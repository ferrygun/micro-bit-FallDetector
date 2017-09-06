#!/bin/bash
asterisk -rx 'channel originate SIP/pstn/xxxxxxxx extension s@from-trunk'
echo 'call'
