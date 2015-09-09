#pragma once
#ifndef __PRIMARY_MATRIX_BASE_H__
#define __PRIMARY_MATRIX_BASE_H__

#include "math/config.h"
#include "math/generic/genericMatrixData.h"

BEGIN_MATH_NAMESPACE

template< class TYPE, U32 ROWS, U32 COLS >
class PrimaryMatrixBase : public GenericMatrixData< TYPE, ROWS, COLS >
{
public:

    // Accessors
    inline const PrimaryVectorBase< TYPE, COLS > & operator[](U32 i) const
    {
        assert(i < ROWS);

        return this->mRows[i];
    }

    inline PrimaryVectorBase< TYPE, COLS > &operator[](U32 i)
    {
        assert(i < ROWS);

        return this->mRows[i];
    }

    inline PrimaryMatrixBase< TYPE, ROWS, COLS > &operator=(const PrimaryMatrixBase< TYPE, ROWS, COLS > &m)
    {
        for (U32 i = 0; i < ROWS; ++i)
        {
            for (U32 j = 0; j < COLS; ++j)
            {
                this->mRows[i][j] = m.mRows[i][j];
            }
        };

        return *this;
    }

    inline PrimaryMatrixBase< TYPE, ROWS, COLS > &operator*=(const PrimaryMatrixBase< TYPE, ROWS, COLS > &m)
    {
        for (U32 i = 0; i < ROWS; ++i)
        {
            for (U32 j = 0; j < COLS; ++j)
            {
                m.DotColumn(j, this->mRows[i]);
            }
        }

        return *this;
    }

    inline PrimaryMatrixBase< TYPE, ROWS, COLS > &operator+=(const PrimaryMatrixBase< TYPE, ROWS, COLS > &m)
    {
        for (U32 i = 0; i < ROWS; ++i)
        {
            for (U32 j = 0; j < COLS; ++j)
            {
                this->mRows[i][j] += m.mRows[i][j];
            }
        }

        return *this;
    }

    inline PrimaryMatrixBase< TYPE, ROWS, COLS > &operator-=(const PrimaryMatrixBase< TYPE, ROWS, COLS > &m)
    {
        for (U32 i = 0; i < ROWS; ++i)
        {
            for (U32 j = 0; j < COLS; ++j)
            {
                this->mRows[i][j] -= m.mRows[i][j];
            }
        }

        return *this;
    }

    inline bool operator==(const PrimaryMatrixBase< TYPE, ROWS, COLS > &m) const
    {
        bool result = true;

        for (U32 i = 0; i < ROWS; ++i)
        {
            for (U32 j = 0; j < COLS; ++j)
            {
                result &= this->mRows == m.mRows;
            }
        }

        return result;
    }

    inline bool operator!=(const PrimaryMatrixBase< TYPE, ROWS, COLS > &m) const
    {
        return !(*this == m);
    }

    inline void SetColumn(const U8 column, const PrimaryVectorBase< TYPE, ROWS > &v)
    {
        for (U32 j = 0; j < COLS; ++j)
        {
            this->mRows[j][column] = v[j];
        }
    }

    inline PrimaryVectorBase< TYPE, ROWS > GetColumn(const U8 column) const
    {
        PrimaryVectorBase< TYPE, COLS > newVec;

        for (U32 j = 0; j < COLS; ++j)
        {
            newVec[j] = this->mRows[j][column];
        }

        return newVec;
    }

    inline void SetRow(const U8 row, const PrimaryVectorBase< TYPE, COLS > &v)
    {
        this->mRows[row] = v;
    }

    inline PrimaryVectorBase< TYPE, COLS > GetRow(const U8 row) const
    {
        return this->mRows[row];
    }

    inline PrimaryMatrixBase< TYPE, ROWS, COLS > Scale(const PrimaryVectorBase< TYPE, COLS > &v) const
    {
        PrimaryMatrixBase< TYPE, ROWS, COLS > newMat;

        for (U32 i = 0; i < ROWS; ++i)
        {
            newMat.SetRow( this->mRows[i] * v );
        }

        return newMat;
    }

    inline PrimaryMatrixBase< TYPE, COLS, ROWS > GetTranspose() const
    {
        PrimaryMatrixBase< TYPE, COLS, ROWS > transpMat;

        for (U32 i = 0; i < ROWS; ++i)
        {
            transpMat.SetColumn(i, this->mRows[i]);
        }

        return transpMat;
    }

    inline PrimaryMatrixBase< TYPE, ROWS, COLS > GetAbsolute() const
    {
        PrimaryMatrixBase< TYPE, ROWS, COLS > newMat;

        for (U32 i = 0; i < ROWS; ++i)
        {
            newMat.SetRow(i, this->mRows[i].Absolute() );
        }
        
        return newMat;
    }

    inline TYPE GetCofactor(const U8 row, const U8 column) const
    {
        // Make an matrix that is -1 smaller in ROWS and COLS
        PrimaryMatrixBase< TYPE, ROWS - 1, COLS - 1 > localMat;

        U32 irow = 0;

        for (U32 i = 0; i < ROWS; ++i)
        {
            if (i == row)
            {
                continue;
            }

            U32 jcol = 0;

            for (U32 j = 0; j < COLS; ++j)
            {
                if (j == column)
                {
                    continue;
                }

                localMat[irow][jcol] = this->mRows[i][j];

                jcol++;
            }

            irow++;
        }


        TYPE cof = localMat.GetDeterminant();

        if (((column + row) & 1) == 1)
        {
            cof *= -1;
        }

        return cof;
    }

    inline PrimaryMatrixBase< TYPE, ROWS, COLS > GetAdjoint() const
    {
        PrimaryMatrixBase< TYPE, ROWS, COLS > localMat;

        for (U32 i = 0; i < ROWS; ++i)
        {
            for (U32 j = 0; j < COLS; ++j)
            {
                localMat[i][j] = GetCofactor(i, j);
            }
        }

        return localMat;
    }

    inline PrimaryMatrixBase< TYPE, ROWS, COLS > GetInverse() const
    {
        const TYPE det = GetDeterminant();

        assert( det != 0.0f );

        const TYPE s = 1.0f / det;
        return GetAdjoint().GetTranspose() * s;
    }

    inline void SetIdentity()
    {
        for (U32 i = 0; i < ROWS; ++i)
        {
            for (U32 j = 0; j < COLS; ++j)
            {
                if (i == j)
                {
                    this->mRows[i][j] = 1.0;
                }
                else
                {
                    this->mRows[i][j] = 0.0;
                }    
            }
        }
    }

    

    inline TYPE GetDeterminant() const
    {
        TYPE result = 0;

        for (U32 i = 0; i < ROWS; ++i)
        {
            result += this->mRows[i][0] * GetCofactor(i, 0);
        }

        return result;
    }

    static inline PrimaryMatrixBase< TYPE, ROWS, COLS > GetZero()
    {
        PrimaryMatrixBase< TYPE, ROWS, COLS > localMat;

        for (U32 i = 0; i < ROWS; ++i)
        {
            for (U32 j = 0; j < COLS; ++j)
            {
                localMat[i][j] = 0.0;
            }
        }

        return localMat;
    }

    static inline PrimaryMatrixBase< TYPE, ROWS, COLS > GetIdentity()
    {
        PrimaryMatrixBase< TYPE, ROWS, COLS > mat;
        mat.SetIdentity();
        return mat;
    }

private:

    inline TYPE DotColumn( U32 tcol, const PrimaryVectorBase< TYPE, ROWS > &v) const
    {
        TYPE result = 0;

        for (U32 i = 0; i < ROWS; ++i)
        {
            this->mRows[i][tcol] * v[tcol];
        }

        return result;
    }
};

END_MATH_NAMESPACE


#endif