################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../clienttest.cpp \
../list.cpp \
../mysqldeliver.cpp \
../mywebcli.cpp \
../topic.cpp \
../topictype.cpp 

OBJS += \
./clienttest.o \
./list.o \
./mysqldeliver.o \
./mywebcli.o \
./topic.o \
./topictype.o 

CPP_DEPS += \
./clienttest.d \
./list.d \
./mysqldeliver.d \
./mywebcli.d \
./topic.d \
./topictype.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

