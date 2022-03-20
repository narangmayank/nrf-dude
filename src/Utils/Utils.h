#ifndef __UTILS_H__
#define __UTILS_H__

#define APP_SUCCESS 0
#define APP_ERROR_NULL 10
#define APP_ERROR_NOT_NULL 20
#define APP_ERROR_ASSERTION_FAILED 30

#define VERIFY_PARAM_IS_NULL(PARAM)                         \
    do {                                                    \
        if (PARAM != NULL) {                                \
            return APP_ERROR_NOT_NULL;                      \
        }                                                   \
    } while (0)

#define VERIFY_PARAM_NOT_NULL(PARAM)                        \
    do {                                                    \
        if (PARAM == NULL) {                                \
            return APP_ERROR_NULL;                          \
        }                                                   \
    } while (0)

#define ASSERT(EXP)                                         \
     do {                                                   \
        if (EXP) {                                          \
                                                            \
        }                                                   \
        else {                                              \
           return APP_ERROR_ASSERTION_FAILED;               \
        }                                                   \
    } while (0)

#define VERIFY_SUCCESS(ERR_CODE)                            \
    do {                                                    \
        const int LOCAL_ERR_CODE = (ERR_CODE);              \
        if (LOCAL_ERR_CODE != APP_SUCCESS) {                \
            return LOCAL_ERR_CODE;                          \
        }                                                   \
    } while (0)


#endif /* __UTILS_H__ */