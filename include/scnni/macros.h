/*
 * @Author: zzh
 * @Description: 
 * @FilePath: /scnni/include/scnni/macros.h
 */
#pragma once

#include <cassert>
#include <stdexcept>

namespace scnni {

#define SCNNI_ASSERT(expr, message) assert((expr) && (message))

#define UNIMPLEMENTED(message) throw std::logic_error(message)

#define SCNNI_ENSURE(expr, message) \
  if (!(expr)) {                     \
    throw std::logic_error(message); \
  }

#define UNREACHABLE(message) throw std::logic_error(message)

// Macros to disable copying and moving
#define DISALLOW_COPY(cname)                                    \
  cname(const cname &) = delete;                   /* NOLINT */ \
  auto operator=(const cname &)->cname & = delete; /* NOLINT */

#define DISALLOW_MOVE(cname)                               \
  cname(cname &&) = delete;                   /* NOLINT */ \
  auto operator=(cname &&)->cname & = delete; /* NOLINT */

#define DISALLOW_COPY_AND_MOVE(cname) \
  DISALLOW_COPY(cname);               \
  DISALLOW_MOVE(cname);

}  // namespace scnni
