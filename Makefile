TARGET_NAME := template

PATH_SOURCE := src
PATH_BUILD  := build

SRCS   := $(wildcard $(PATH_SOURCE)/*.c)
TARGET := $(PATH_BUILD)/$(TARGET_NAME)

include $(NOLIBGS_PATH)/common.mk
