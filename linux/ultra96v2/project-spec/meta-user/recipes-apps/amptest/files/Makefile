
APP = amptest
APP_OBJS = amp_test.o

APP1 = rpmsgdelaytest
APP_OBJS1 = rpmsg_delay_test.o

# Add any other object files to this list below


all: $(APP) $(APP1)

$(APP): $(APP_OBJS)
	$(CC) $(LDFLAGS) -o $@ $(APP_OBJS) $(LDLIBS)

$(APP1): $(APP_OBJS1)
	$(CC) $(LDFLAGS) -o $@ $(APP_OBJS1) $(LDLIBS)

clean:
	rm -rf $(APP) $(APP1)*.o

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

