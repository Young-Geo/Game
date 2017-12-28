CC = gcc  
  
ROOT := $(shell pwd) 
ehco $(ROOT) 
INCLUDE := $(ROOT)/include  
SRC := $(ROOT)  
  
USR_SUB_DIR := $(SRC)/YGameDB $(SRC)/YGameDesk  $(SRC)/YGameManage  
  
default:usr  
  
usr:  
    @for n in $(USR_SUB_DIR); do $(MAKE) -C $$n ; done  
      
clean:  
    @for n in $(USR_SUB_DIR); do $(MAKE) -C $$n clean; done