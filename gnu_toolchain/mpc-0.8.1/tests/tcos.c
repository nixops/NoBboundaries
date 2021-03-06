/* test file for mpc_cos.

Copyright (C) 2008, 2009 Andreas Enge, Philippe Th\'eveny

This file is part of the MPC Library.

The MPC Library is free software; you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 2.1 of the License, or (at your
option) any later version.

The MPC Library is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
License for more details.

You should have received a copy of the GNU Lesser General Public License
along with the MPC Library; see the file COPYING.LIB.  If not, write to
the Free Software Foundation, Inc., 59 Temple Place - Suite 330, Boston,
MA 02111-1307, USA. */

#include "mpc-tests.h"

static void
bug20090105 (void)
{
  /* this bug appeared on 32-bits machines */
  mpc_t op, expected, got;
  mpc_init2 (op, 324);
  mpc_init2 (expected, 324);
  mpc_init2 (got, 324);

  mpfr_set_str (MPC_RE(op), "-3.f1813b1487372434fea4414a520f65a343a16d0ec1ffb"
                "b2b880154db8d63377ce788fc4215c450300@1", 16, GMP_RNDN);
  mpfr_set_str (MPC_IM(op), "-2.b7a0c80bcacf1ccbbac614bf53a58b672b1b503161bee"
                "59a82e46a23570b652f7ba5f01ef766d1c50", 16,GMP_RNDN);
  mpfr_set_str (MPC_RE(expected), "7.57c5b08a2b11b660d906a354289b0724b9c4b237"
                "95abe33424e8d9858e534bd5d776ddd18e34b0240", 16, GMP_RNDN);
  mpfr_set_str (MPC_IM(expected), "-1.f41a389646d068e0263561cb3c5d1df763945ad"
                "ed9339f2a98387a3c4f97dbfd8a08b7d0af2f11b46", 16,GMP_RNDN);

  mpc_cos (got, op, MPC_RNDNN);
  if (mpc_cmp (got, expected) != 0)
    {
      printf ("Error in bug20090105: cos(op) with rounding mode MPC_RNDNN\n");
      OUT (op);
      OUT (expected);
      printf("     ");
      OUT (got);

      exit (1);
    }

  mpc_clear (got);
  mpc_clear(expected);
  mpc_clear (op);
}

int
main (void)
{
  DECL_FUNC (CC, f, mpc_cos);

  test_start ();

  data_check (f, "cos.dat");
  tgeneric (f, 2, 512, 7, 7);

  bug20090105 ();

  test_end ();

  return 0;
}
