/*
 
 Copyright (c) 2012, SMB Phone Inc.
 All rights reserved.
 
 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:
 
 1. Redistributions of source code must retain the above copyright notice, this
 list of conditions and the following disclaimer.
 2. Redistributions in binary form must reproduce the above copyright notice,
 this list of conditions and the following disclaimer in the documentation
 and/or other materials provided with the distribution.
 
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 
 The views and conclusions contained in the software and documentation are those
 of the authors and should not be interpreted as representing official policies,
 either expressed or implied, of the FreeBSD Project.
 
 */

#pragma once

#include <hookflash/stack/hookflashTypes.h>
#include <hookflash/stack/message/hookflashTypes.h>
#include <zsLib/Proxy.h>


namespace hookflash
{
  namespace stack
  {
    interaction IMessageRequester
    {
      typedef zsLib::Duration Duration;
      typedef zsLib::String String;

      static IMessageRequesterPtr monitorRequest(
                                                 IMessageRequesterDelegatePtr delegate,
                                                 message::MessagePtr requestMessage,
                                                 Duration timeout
                                                 );

      static bool handleMessage(message::MessagePtr message);

      virtual bool wasHandled() const = 0;
      virtual bool isComplete() const = 0;

      virtual void cancel() = 0;

      virtual message::MessagePtr getMonitoredMessage() = 0;
      virtual String getMonitoredMessageID() = 0;
    };

    interaction IMessageRequesterDelegate
    {
      virtual bool handleMessageRequesterMessageReceived(
                                                         IMessageRequesterPtr requester,
                                                         message::MessagePtr message
                                                         ) = 0;

      virtual void onMessageRequesterTimedOut(IMessageRequesterPtr requester) = 0;
    };
  }
}

ZS_DECLARE_PROXY_BEGIN(hookflash::stack::IMessageRequesterDelegate)
ZS_DECLARE_PROXY_METHOD_SYNC_RETURN_2(handleMessageRequesterMessageReceived, bool, hookflash::stack::IMessageRequesterPtr, hookflash::stack::message::MessagePtr)
ZS_DECLARE_PROXY_METHOD_1(onMessageRequesterTimedOut, hookflash::stack::IMessageRequesterPtr)
ZS_DECLARE_PROXY_END()
