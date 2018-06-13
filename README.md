## Task 1

1. Copy paste project ...
1. Open project file ...
1. Set build configuration to Debug. This will provide more useful info to be prented out to serial terminals, and makes it easier to step though code with debugger. 
4. Initialize [Logger module] (INSERT LINK)
5. Configure logger to use RTT. (WHat happens with FLSH requirements)
1. Configure logger severity level (WHat happens with FLSH requirements)
1. enable debugger 

        static void log_init(void)
        {
            ret_code_t err_code = NRF_LOG_INIT(NULL);
            APP_ERROR_CHECK(err_code);
            NRF_LOG_DEFAULT_BACKENDS_INIT();
        }

    asdf

1. Print debug message
1. Start debugger and look for debug message in SES's Debug Terminal. 
1. Try out APP_ERROR_CHECK(1)