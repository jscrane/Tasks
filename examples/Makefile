ALL = Blink Channel Deadlock Devices Philosophers Signal
BOARDS = t85db uno fr5739 g2553
TARGETS = $(foreach a, $(ALL), $(foreach b,$(BOARDS), $(a)/$(b)))

.PHONY: all $(TARGETS)

all: $(TARGETS)

$(TARGETS):
	$(MAKE) -C $(dir $@) -f $(notdir $@) clean all
