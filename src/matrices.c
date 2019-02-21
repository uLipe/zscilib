/*
 * Copyright (c) 2019 Kevin Townsend (KTOWN)
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <string.h>
#include <zsl/zsl.h>
#include <zsl/matrices.h>

/*
 * WARNING: Work in progress!
 *
 * The code in this module is very 'naive' in the sense that no attempt
 * has been made at efficiency. It is written from the perspective
 * that code should be written to be 'reliable, elegant, efficient' in that
 * order.
 *
 * Clarity and reliability have been absolutely prioritized in this
 * early stage, with the key goal being good unit test coverage before
 * moving on to any form of general-purpose or architecture-specific
 * optimisation.
 */

int
zsl_mtx_entry_fn_empty(struct zsl_mtx *m, size_t i, size_t j)
{
    /* TODO: Consider inlining to avoid multiple unnecessary branches. */

    return zsl_mtx_set(m, i, j, 0);
}

int
zsl_mtx_entry_fn_diagonal(struct zsl_mtx *m, size_t i, size_t j)
{
    /* TODO: Consider inlining to avoid multiple unnecessary branches. */

    return zsl_mtx_set(m, i, j, i == j ? 1.0 : 0);
}

int
zsl_mtx_entry_fn_random(struct zsl_mtx *m, size_t i, size_t j)
{
    /* TODO: Consider inlining to avoid multiple unnecessary branches. */

    /* TODO: Determine an appropriate random number generator. */
    return zsl_mtx_set(m, i, j, 0);
}

int
zsl_mtx_init(struct zsl_mtx *m, zsl_mtx_init_entry_fn_t entry_fn)
{
    int rc;

    for (size_t i = 0; i < m->sz_rows; i++) {
        for (size_t j = 0; j < m->sz_cols; j++) {
            /* If entry_fn is NULL, assign 0.0 values. */
            if (entry_fn == NULL) {
                rc = zsl_mtx_entry_fn_empty(m, i, j);
            } else {
                rc = entry_fn(m, i, j);
            }
            /* Abort if entry_fn returned an error code. */
            if (rc) {
                goto err;
            }
        }
    }

    return 0;
err:
    return rc;
}

int
zsl_mtx_from_arr(struct zsl_mtx *m, zsl_real_t *a)
{
    /* TODO: Evaluate inlining function to avoid repetitive branches. */

    memcpy(m->data, a, (m->sz_rows * m->sz_cols) * sizeof(zsl_real_t));

    return 0;
}

int
zsl_mtx_get(struct zsl_mtx *m, size_t i, size_t j, zsl_real_t *x)
{
    /* TODO: Evaluate inlining function to avoid repetitive branches. */

    if ((i >= m->sz_rows) || (j >= m->sz_cols)) {
        return -EINVAL;
    }

    *x = m->data[(i * m->sz_cols) + j];

    return 0;
}

int
zsl_mtx_set(struct zsl_mtx *m, size_t i, size_t j, zsl_real_t x)
{
    /* TODO: Evaluate inlining function to avoid repetitive branches. */

    if ((i >= m->sz_rows) || (j >= m->sz_cols)) {
        return -EINVAL;
    }

    m->data[(i * m->sz_cols) + j] = x;

    return 0;
}

int
zsl_mtx_get_row(struct zsl_mtx *m, size_t i, zsl_real_t *v)
{
    int rc;
    zsl_real_t x;

    /*
     * TODO: Optimise by determining start pos and perform consecutive
     * reads for sz_rows values, avoiding multiple unnecessary branches.
     */

    for (size_t j = 0; j < m->sz_cols; j++) {
        rc = zsl_mtx_get(m, i, j, &x);
        if (rc) {
            return rc;
        }
        v[j] = x;
    }

    return 0;
}

int
zsl_mtx_set_row(struct zsl_mtx *m, size_t i, zsl_real_t *v)
{
    int rc;

    /*
     * TODO: Optimise by determining start pos and perform consecutive
     * writes for sz_rows values, avoiding multiple unnecessary branches.
     */

    for (size_t j = 0; j < m->sz_cols; j++) {
        rc = zsl_mtx_set(m, i, j, v[j]);
        if (rc) {
            return rc;
        }
    }

    return 0;
}

int
zsl_mtx_get_col(struct zsl_mtx *m, size_t j, zsl_real_t *v)
{
    int rc;
    zsl_real_t x;

    /*
     * TODO: Optimise by determining start pos and perform consecutive
     * reads every sz_rows values for sz_cols entries, avoiding multiple
     * unnecessary branches.
     */

    for (size_t i = 0; i < m->sz_rows; i++) {
        rc = zsl_mtx_get(m, i, j, &x);
        if (rc) {
            return rc;
        }
        v[i] = x;
    }

    return 0;
}

int
zsl_mtx_set_col(struct zsl_mtx *m, size_t j, zsl_real_t *v)
{
    int rc;

    /*
     * TODO: Optimise by determining start pos and perform consecutive
     * writes every sz_rows values for sz_cols entries, avoiding multiple
     * unnecessary branches.
     */

    for (size_t i = 0; i < m->sz_rows; i++) {
        rc = zsl_mtx_set(m, i, j, v[i]);
        if (rc) {
            return rc;
        }
    }

    return 0;
}

int
zsl_mtx_add(struct zsl_mtx *ma, struct zsl_mtx *mb, struct zsl_mtx *mc)
{
    /* TODO: Add inline helper to validate shape of multiple matrices. */

    if ((ma->sz_rows != mb->sz_rows) || (mb->sz_rows != mc->sz_rows) ||
        (ma->sz_cols != mb->sz_cols) || (mb->sz_cols != mc->sz_cols)) {
        return -EINVAL;
    }

    /* TODO: Evaluate if a while(i--) loop would be faster reading sz once. */

    for (size_t i = 0; i < ma->sz_cols * ma->sz_rows; i++) {
        mc->data[i] = ma->data[i] + mb->data[i];
    }

    return 0;
}

int
zsl_mtx_add_d(struct zsl_mtx *ma, struct zsl_mtx *mb)
{
    return zsl_mtx_add(ma, mb, ma);
}

int
zsl_mtx_sub(struct zsl_mtx *ma, struct zsl_mtx *mb, struct zsl_mtx *mc)
{
    /* TODO: Add inline helper to validate shape of multiple matrices. */

    if ((ma->sz_rows != mb->sz_rows) || (mb->sz_rows != mc->sz_rows) ||
        (ma->sz_cols != mb->sz_cols) || (mb->sz_cols != mc->sz_cols)) {
        return -EINVAL;
    }

    /* TODO: Evaluate if a while(i--) loop would be faster reading sz once. */

    for (size_t i = 0; i < ma->sz_cols * ma->sz_rows; i++) {
        mc->data[i] = ma->data[i] - mb->data[i];
    }

    return 0;
}

int
zsl_mtx_sub_d(struct zsl_mtx *ma, struct zsl_mtx *mb)
{
    return zsl_mtx_sub(ma, mb, ma);
}

int
zsl_mtx_mult(struct zsl_mtx *ma, struct zsl_mtx *mb, struct zsl_mtx *mc)
{
    /* Ensure that ma has the same number as columns as mb has rows. */
    if (ma->sz_cols != mb->sz_rows) {
        return -EINVAL;
    }

    /* Ensure that mc has ma rows and mb cols */
    if ((mc->sz_rows != ma->sz_rows) || (mc->sz_cols != mb->sz_cols)) {
        return -EINVAL;
    }

    for (size_t i = 0; i < ma->sz_rows; i++) {
        for (size_t j = 0; j < mb->sz_cols; j++) {
            mc->data[j + i * mb->sz_cols] = 0;
            for (size_t k = 0; k < ma->sz_cols; k++) {
                mc->data[j + i * mb->sz_cols] +=
                    ma->data[k + i * ma->sz_cols] *
                    mb->data[j + k * mb->sz_cols];
            }
        }
    }

    return 0;
}

int
zsl_mtx_scalar_mult(struct zsl_mtx *m, zsl_real_t s)
{
    for (size_t i = 0; i < m->sz_cols * m->sz_rows; i++) {
        m->data[i] *= s;
    }

    return 0;
}

int
zsl_mtx_trans(struct zsl_mtx *ma, struct zsl_mtx *mb)
{
    /* Ensure that ma and mb have the same shape. */
    if ((ma->sz_rows != mb->sz_cols) || (ma->sz_cols != mb->sz_rows)) {
        return -EINVAL;
    }

    zsl_real_t d[ma->sz_cols];

    for (size_t i = 0; i < ma->sz_rows; i++) {
        zsl_mtx_get_row(ma, i, d);
        zsl_mtx_set_col(mb, i, d);
    }

    return 0;
}
