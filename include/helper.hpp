#ifndef THROW_HELPER
#define THROW_HELPER
#define HELPER_THROW(func, type, msg)                                          \
  EXPECT_THROW(                                                                \
      {                                                                        \
        try {                                                                  \
          func;                                                                \
        } catch (const type &e) {                                              \
          EXPECT_STREQ(msg, e.what());                                         \
          throw;                                                               \
        }                                                                      \
      },                                                                       \
      type);
#endif
