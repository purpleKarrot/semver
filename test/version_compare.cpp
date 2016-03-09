// Copyright (c) 2016, Daniel Pfeifer <daniel@pfeifer-mail.de>
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
// WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
// ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
// WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
// ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
// OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

#include <semver/version_compare.hpp>
#include <boost/detail/lightweight_test.hpp>

int version_compare(int, char**)
{
  using semver::Operator;
  using semver::version_compare;

  BOOST_TEST(version_compare("1.00123", "1.123", Operator::equal));
  BOOST_TEST(version_compare("1.123", "1.00123", Operator::equal));

  BOOST_TEST(version_compare("1.25", "1.24", Operator::equal) == false);
  BOOST_TEST(version_compare("1.25", "1.25", Operator::equal) == true);
  BOOST_TEST(version_compare("1.25", "1.26", Operator::equal) == false);

  BOOST_TEST(version_compare("1.25", "1.24", Operator::less_than) == false);
  BOOST_TEST(version_compare("1.25", "1.25", Operator::less_than) == false);
  BOOST_TEST(version_compare("1.25", "1.26", Operator::less_than) == true);

  BOOST_TEST(version_compare("1.25", "1.24", Operator::less_equal) == false);
  BOOST_TEST(version_compare("1.25", "1.25", Operator::less_equal) == true);
  BOOST_TEST(version_compare("1.25", "1.26", Operator::less_equal) == true);

  BOOST_TEST(version_compare("1.25", "1.24", Operator::greater_than) == true);
  BOOST_TEST(version_compare("1.25", "1.25", Operator::greater_than) == false);
  BOOST_TEST(version_compare("1.25", "1.26", Operator::greater_than) == false);

  BOOST_TEST(version_compare("1.25", "1.24", Operator::greater_equal) == true);
  BOOST_TEST(version_compare("1.25", "1.25", Operator::greater_equal) == true);
  BOOST_TEST(version_compare("1.25", "1.26", Operator::greater_equal) == false);

  BOOST_TEST(version_compare("1.25", "1.24", Operator::not_equal) == true);
  BOOST_TEST(version_compare("1.25", "1.25", Operator::not_equal) == false);
  BOOST_TEST(version_compare("1.25", "1.26", Operator::not_equal) == true);

  return boost::report_errors();
}
