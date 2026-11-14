# Shared logging system

SILENT := 0
ERROR  := 1
WARN   := 2
INFO   := 3
NOTICE := 4
DEBUG  := 5
TRACE  := 6
LOG_LEVEL ?= $(NOTICE)

ifeq ($(shell echo $$(( $(LOG_LEVEL) >= $(ERROR) ))),1)
define fail
	$(shell echo "echo '[ERROR]\033[31m $1\033[m'"); \
	exit 1
endef
else
fail   = :
endif

ifeq ($(shell echo $$(( $(LOG_LEVEL) >= $(WARN) ))),1)
warn   = $(shell echo "echo '[WARN] \033[33m $1\033[m'")
else
warn   = :
endif

ifeq ($(shell echo $$(( $(LOG_LEVEL) >= $(INFO) ))),1)
inform = $(shell echo "echo '[INFO] \033[35m $1\033[m'")
else
inform = :
endif

ifeq ($(shell echo $$(( $(LOG_LEVEL) >= $(NOTICE) ))),1)
notice = $(shell echo "echo '[NOTE] \033[32m $1\033[m'")
else
notice = :
endif

ifeq ($(shell echo $$(( $(LOG_LEVEL) >= $(DEBUG) ))),1)
debug  = $(shell echo "echo '[DEBG] \033[36m $1\033[m'")
else
debug    = :
endif

ifeq ($(shell echo $$(( $(LOG_LEVEL) >= $(TRACE) ))),1)
trace  = $(shell echo "echo '[TRCE] \033[37m $1\033[m'")
else
trace  = :
endif

