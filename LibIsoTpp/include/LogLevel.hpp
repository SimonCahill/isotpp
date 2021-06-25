/**
 * @file LogLevel.hpp
 * @author Simon Cahill (simonc@online.de)
 * @brief Contains the declaration for different logging levels used by IsoTpp
 * @version 0.1
 * @date 2021-06-25
 * 
 * @copyright Copyright (c) 2021 Simon Cahill and Contributors
 */

#ifndef ISOTPP_INCLUDE_LOGLEVEL_HPP
#define ISOTPP_INCLUDE_LOGLEVEL_HPP

namespace isotpp {

    /**
     * @brief Enumeration containing the different log levels used by IsoTpp.
     */
    enum class LogLevel {
        /**
         * @brief A debug message: should not be shown to end-users.
         */
        Debug = 6,

        /**
         * @brief An error has occurred. The application may be able to recover.
         */
        Error = 4,

        /**
         * @brief A fatal error has occurred. Stop what you're doing immediately.
         */
        Fatal = 5,

        /**
         * @brief An informational message. Neither good, nor bad.
         */
        Info = 1,

        /**
         * @brief An message indicating that everything is working as originally intended.
         */
        Okay = 0,

        /**
         * @brief A warning message: maybe the iron is getting too hot after all?
         */
        Warning = 3
    };

}

#endif // ISOTPP_INCLUDE_LOGLEVEL_HPP