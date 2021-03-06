/*
 * Copyright (C) 2008 Apple Inc. All rights reserved.
 * Copyright (c) 2011 ACCESS CO., LTD. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
 */

#ifndef CachedScriptSourceProvider_h
#define CachedScriptSourceProvider_h

#include "CachedResourceClient.h"
#include "CachedResourceHandle.h"
#include "CachedScript.h"
#include "ScriptSourceProvider.h"
#include <parser/SourceCode.h>

namespace WebCore {

    class CachedScriptSourceProvider : public ScriptSourceProvider, public CachedResourceClient {
    public:
        static PassRefPtr<CachedScriptSourceProvider> create(CachedScript* cachedScript) { return adoptRef(new CachedScriptSourceProvider(cachedScript)); }

        virtual ~CachedScriptSourceProvider()
        {
            m_cachedScript->removeClient(this);
        }

#if PLATFORM(WKC)
        JSC::UString getRange(int start, int end) const
        {
            String source = m_cachedScript->script();
            return (source.isEmpty() ? JSC::UString() : JSC::UString(source.characters() + start, end - start));
        }
#else
        JSC::UString getRange(int start, int end) const { return JSC::UString(m_cachedScript->script().characters() + start, end - start); }
#endif
        const UChar* data() const { return m_cachedScript->script().characters(); }
        int length() const { return m_cachedScript->script().length(); }
        const String& source() const { return m_cachedScript->script(); }

    private:
        CachedScriptSourceProvider(CachedScript* cachedScript)
            : ScriptSourceProvider(cachedScript->url())
            , m_cachedScript(cachedScript)
        {
            m_cachedScript->addClient(this);
        }

        CachedResourceHandle<CachedScript> m_cachedScript;
    };

    inline JSC::SourceCode makeSource(CachedScript* cachedScript)
    {
        return JSC::SourceCode(CachedScriptSourceProvider::create(cachedScript));
    }

} // namespace WebCore

#endif // CachedScriptSourceProvider_h
