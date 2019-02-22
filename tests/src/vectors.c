/*
 * Copyright (c) 2019 Kevin Townsend (KTOWN)
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <ztest.h>
#include <zsl/zsl.h>
#include <zsl/vectors.h>
#include "floatcheck.h"

/**
 * @brief zsl_vec_from_arr unit tests.
 *
 * This test verifies the zsl_vec_from_arr function.
 */
void test_vector_from_arr(void)
{
    int rc;
    zsl_real_t x;

    /* Destination vector. */
    ZSL_VECTOR_DEF(v, 3);

    /* Test array. */
    zsl_real_t a[3] = { 0.0, 1.0, 2.0 };

    /* Initialise the vector. */
    rc = zsl_vec_init(&v);
    zassert_true(rc == 0, "from_arr:vec_init != 0");

    /* Assign the array a to vector v. */
    rc = zsl_vec_from_arr(&v, a);
    zassert_true(rc == 0, "from_arr:ret != 0");

    /* Test values. */
    for (size_t i = 0; i < v.sz; i++) {
        x = v.data[i];
        zassert_true(x == a[i], "from_arr:unexpected val in .data");
    }
}

void test_vector_from_arr_ret(void)
{

}

void test_vector_get_subset(void)
{

}

void test_vector_add(void)
{
    int rc;

    ZSL_VECTOR_DEF(va, 3);
    ZSL_VECTOR_DEF(vb, 3);
    ZSL_VECTOR_DEF(vc, 3);

    zsl_real_t a[3] = { 0.0, 1.0, 2.0 };
    zsl_real_t b[3] = {-1.0, 0.5, 0.1 };
    zsl_real_t c[3] = {-1.0, 1.5, 2.1 };

    /* Initialise the vectors. */
    zsl_vec_init(&va);
    zsl_vec_init(&vb);
    zsl_vec_init(&vc);

    /* Assign arrays to vectors. */
    rc = zsl_vec_from_arr(&va, a);
    zassert_true(rc == 0, "");
    rc = zsl_vec_from_arr(&vb, b);
    zassert_true(rc == 0, "");

    /* Perform the add operation. */
    rc = zsl_vec_add(&va, &vb, &vc);
    zassert_true(rc == 0, "");
    zassert_equal(vc.data[0], c[0], "");
    zassert_equal(vc.data[1], c[1], "");
    zassert_equal(vc.data[2], c[2], "");
}

void test_vector_sub(void)
{
    int rc;

    ZSL_VECTOR_DEF(va, 3);
    ZSL_VECTOR_DEF(vb, 3);
    ZSL_VECTOR_DEF(vc, 3);

    zsl_real_t a[3] = { 0.0, 1.0, 2.0 };
    zsl_real_t b[3] = {-1.0, 0.5, 0.1 };
    zsl_real_t c[3] = { 1.0, 0.5, 1.9 };

    /* Initialise the vectors. */
    zsl_vec_init(&va);
    zsl_vec_init(&vb);
    zsl_vec_init(&vc);

    /* Assign arrays to vectors. */
    rc = zsl_vec_from_arr(&va, a);
    zassert_true(rc == 0, "");
    rc = zsl_vec_from_arr(&vb, b);
    zassert_true(rc == 0, "");

    /* Perform the add operation. */
    rc = zsl_vec_sub(&va, &vb, &vc);
    zassert_true(rc == 0, "");
    zassert_equal(vc.data[0], c[0], "");
    zassert_equal(vc.data[1], c[1], "");
    zassert_equal(vc.data[2], c[2], "");
}

void test_vector_neg(void)
{
    int rc;

    ZSL_VECTOR_DEF(v, 3);

    zsl_real_t a[3] = {  0.0,  1.0,  2.0 };
    zsl_real_t b[3] = { -0.0, -1.0, -2.0 };

    /* Initialise the vectors. */
    zsl_vec_init(&v);

    /* Assign array to vector. */
    rc = zsl_vec_from_arr(&v, a);
    zassert_true(rc == 0, "");

    /* Perform the add operation. */
    rc = zsl_vec_neg(&v);
    zassert_true(rc == 0, "");
    zassert_equal(v.data[0], b[0], "");
    zassert_equal(v.data[1], b[1], "");
    zassert_equal(v.data[2], b[2], "");
}

void test_vector_sum(void)
{
    int rc;

    ZSL_VECTOR_DEF(va, 3);
    ZSL_VECTOR_DEF(vb, 3);
    ZSL_VECTOR_DEF(vc, 3);
    ZSL_VECTOR_DEF(vsum, 3);

    struct zsl_vec *vlist[3] = { &va, &vb, &vc };

    /* Initialise the vectors. */
    zsl_vec_init(&va);
    zsl_vec_init(&vb);
    zsl_vec_init(&vc);
    zsl_vec_init(&vsum);

    /* Assign values to vectors. */
    va.data[0] = 1.0;
    va.data[1] = 2.0;
    va.data[2] = 3.0;
    vb.data[0] = 3.0;
    vb.data[1] = 2.0;
    vb.data[2] = 1.0;
    vc.data[0] = -1.0;
    vc.data[1] = -2.0;
    vc.data[2] = -3.0;

    /* Perform sum operation on va..vc. */
    rc = zsl_vec_sum(vlist, 3, &vsum);
    zassert_true(rc == 0, "");

    /* Check output. */
    for (size_t i = 0; i <3; i++) {
        zassert_equal(vsum.data[i], va.data[i]+vb.data[i]+vc.data[i], "");
    }
}

void test_vector_magn(void)
{

}

void test_vector_scalar_add(void)
{

}

void test_vector_scalar_mult(void)
{

}

void test_vector_scalar_div(void)
{

}

void test_vector_dist(void)
{

}

void test_vector_dot(void)
{

}

void test_vector_norm(void)
{

}

void test_vector_to_unit(void)
{

}

/**
 * @brief zsl_vec_cross unit tests.
 *
 * This test verifies the zsl_vec_cross function.
 */
void test_vector_cross(void)
{

}

void test_vector_sum_of_sqrs(void)
{

}

void test_vector_mean(void)
{

}

void test_vector_rev(void)
{

}

/**
 * @brief zsl_vec_is_equal unit tests.
 *
 * This test verifies the zsl_vec_is_equal function.
 */
void test_vector_is_equal(void)
{
    int rc;
    bool eq;

    ZSL_VECTOR_DEF(v, 3);
    ZSL_VECTOR_DEF(w, 3);
    ZSL_VECTOR_DEF(x, 2);

    /* Test arrays. */
    zsl_real_t a[3] = { 0.0, 1.0, 2.0 };
    zsl_real_t b[3] = { 0.0, 1.0, 2.0 };

    /* Initialise the vectors. */
    rc = zsl_vec_init(&v);
    zassert_true(rc == 0, "is_equal:initv != 0");
    rc = zsl_vec_init(&w);
    zassert_true(rc == 0, "is_equal:initw != 0");
    rc = zsl_vec_init(&x);
    zassert_true(rc == 0, "is_equal:initx != 0");

    /* Check for unequal size. */
    eq = zsl_vec_is_equal(&v, &x);
    zassert_false(eq, "is_equal:size mismatch");

    /* Check equality for zero value vectors. */
    eq = zsl_vec_is_equal(&v, &w);
    zassert_true(eq, "is_equal:zerovals !equal");

    /* Assign the array a to vector v. */
    rc = zsl_vec_from_arr(&v, a);
    zassert_true(rc == 0, "is_equal:arr:retv != 0");
    rc = zsl_vec_from_arr(&w, b);
    zassert_true(rc == 0, "is_equal:arr:retw != 0");

    /* Check equality for array value vectors. */
    eq = zsl_vec_is_equal(&v, &w);
    zassert_true(eq, "is_equal:vals !equal");

    /* Check for inequality. */
    v.data[0] = 1.0;
    eq = zsl_vec_is_equal(&v, &w);
    zassert_false(eq, "is_equal:vals equal");
}

void test_vector_is_notneg(void)
{

}
