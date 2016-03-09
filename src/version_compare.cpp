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
#include <boost/algorithm/string/predicate.hpp>
#include <cstring>

namespace semver {

static int vercmp(const char* str1, const char* str2)
{
  int ret = 0;
  const char *end1, *end2;

  while (*str1 && *str2) {
    while (*str1 && !std::isalnum(*str1)) {
      ++str1;
    }
    while (*str2 && !std::isalnum(*str2)) {
      ++str2;
    }

    if (std::isdigit(*str1) || std::isdigit(*str2)) {
      while (*str1 == '0' && std::isdigit(str1[1])) {
        ++str1;
      }
      while (*str2 == '0' && std::isdigit(str2[1])) {
        ++str2;
      }

      end1 = str1;
      end2 = str2;
      while (std::isdigit(*end1)) {
        ++end1;
      }
      while (std::isdigit(*end2)) {
        ++end2;
      }

      ret = (end1 - str1) - (end2 - str2);
      if (ret == 0) {
        ret = std::strncmp(str1, str2, end1 - str1);
      }
      if (ret != 0) {
        return ret > 0 ? 1 : -1;
      }

    } else {

      end1 = str1;
      end2 = str2;
      while (std::isalpha(*end1)) {
        end1++;
      }
      while (std::isalpha(*end2)) {
        end2++;
      }

      ret = (end1 - str1) - (end2 - str2);
      if (ret > 0) {
        ret = std::strncmp(str1, str2, end2 - str2);
        return ret >= 0 ? 1 : -1;
      }
      if (ret < 0) {
        ret = std::strncmp(str1, str2, end1 - str1);
        return ret <= 0 ? -1 : 1;
      }

      ret = std::strncmp(str1, str2, end1 - str1);
      if (ret) {
        return ret > 0 ? 1 : -1;
      }
    }

    str1 = end1;
    str2 = end2;
  }

  return *str1 ? 1 : *str2 ? -1 : 0;
}

bool version_compare(std::string const& a, std::string const& b, Operator op,
                     bool compare_branches)
{
  bool const a_is_branch = boost::starts_with(a, "dev-");
  bool const b_is_branch = boost::starts_with(b, "dev-");

  if (a_is_branch && b_is_branch) {
    return op == Operator::equal && vercmp(a.c_str(), b.c_str()) == 0;
  }

  // when branches are not comparable, we make sure dev branches never match
  // anything
  if (!compare_branches && (a_is_branch || b_is_branch)) {
    return false;
  }

  int const compare = vercmp(a.c_str(), b.c_str());
  switch (op) {
    case Operator::equal:
      return compare == 0;
    case Operator::less_than:
      return compare < 0;
    case Operator::less_equal:
      return compare <= 0;
    case Operator::greater_than:
      return compare > 0;
    case Operator::greater_equal:
      return compare >= 0;
    case Operator::not_equal:
      return compare != 0;
  }
}

} // namespace semver
