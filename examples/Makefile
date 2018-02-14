ALL = Blink Channel Deadlock Devices Philosophers Signal
BOARDS = t85db uno fr5739 g2553
TARGETS = $(foreach a, $(ALL), $(foreach b,$(BOARDS), $(a)/$(b).foo))

all: $(TARGETS)

%.foo:
	make -C $(dir $@) -f $(notdir $(basename $@)) clean all
