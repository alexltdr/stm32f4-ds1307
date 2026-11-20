TARGET  = firmware

CC      = arm-none-eabi-gcc
ARCH    = -mcpu=cortex-m4 -mthumb -mfloat-abi=soft

CFLAGS  = -c $(ARCH) -std=gnu11 -Wall -O0 -g -DSTM32F401xE -DUSE_HAL_DRIVER -I. -ICMSIS/Core/Include -ICMSIS/Device/Include -IHAL/Inc
LDFLAGS = $(ARCH) --specs=rdimon.specs -T stm32_ls.ld -Wl,-Map=$(TARGET).map

OBJS = main.o stm32f4xx_it.o stm32f401_startup.o CMSIS/Device/Source/system_stm32f4xx.o \
       HAL/Src/stm32f4xx_hal.o \
       HAL/Src/stm32f4xx_hal_cortex.o \
       HAL/Src/stm32f4xx_hal_rcc.o \
       HAL/Src/stm32f4xx_hal_gpio.o

all: $(TARGET).elf

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

$(TARGET).elf: $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@

clean:
	rm -f $(OBJS) $(TARGET).elf $(TARGET).map

flash: $(TARGET).elf
	openocd -f board/st_nucleo_f4.cfg -c "program $(TARGET).elf verify reset exit"

.PHONY: all clean flash
