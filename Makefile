nodefault:
	@echo "no default target - use one of this:"
	@echo "make clean          to clean each sub-directory"
	@echo "make zip            to create a zip for each sub-directory"

clean:
	@for d in clock-[0-9][0-9]*; do (cd $$d && make clean); done
zip:
	@for d in clock-[0-9][0-9]*; do (cd $$d && make zip); done

.PHONY: nodefault zip clean