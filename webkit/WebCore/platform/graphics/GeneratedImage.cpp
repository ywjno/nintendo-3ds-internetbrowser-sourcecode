/*
 * Copyright (C) 2008 Apple Computer, Inc.  All rights reserved.
 * Copyright (c) 2010,2011 ACCESS CO., LTD. All rights reserved.
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
 * THIS SOFTWARE IS PROVIDED BY APPLE COMPUTER, INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE COMPUTER, INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
 */

#include "config.h"
#include "GeneratedImage.h"

#include "FloatRect.h"
#include "GraphicsContext.h"
#include "ImageBuffer.h"

using namespace std;

namespace WebCore {

void GeneratedImage::draw(GraphicsContext* context, const FloatRect& dstRect, const FloatRect& srcRect, ColorSpace, CompositeOperator compositeOp)
{
#if PLATFORM(WKC)
    CRASH_IF_STACK_OVERFLOW(WKC_STACK_MARGIN_DEFAULT);
#endif
    context->save();
    context->setCompositeOperation(compositeOp);
    context->clip(dstRect);
    context->translate(dstRect.x(), dstRect.y());
    if (dstRect.size() != srcRect.size())
        context->scale(FloatSize(dstRect.width() / srcRect.width(), dstRect.height() / srcRect.height()));
    context->translate(-srcRect.x(), -srcRect.y());
    context->fillRect(FloatRect(FloatPoint(), m_size), *m_generator.get());
    context->restore();
}

void GeneratedImage::drawPattern(GraphicsContext* context, const FloatRect& srcRect, const TransformationMatrix& patternTransform,
                                 const FloatPoint& phase, ColorSpace styleColorSpace, CompositeOperator compositeOp, const FloatRect& destRect)
{
#if PLATFORM(WKC)
    CRASH_IF_STACK_OVERFLOW(WKC_STACK_MARGIN_DEFAULT);
#endif
    // Create a BitmapImage and call drawPattern on it.
    OwnPtr<ImageBuffer> imageBuffer = ImageBuffer::create(m_size);
#if PLATFORM(WKC)
    if (!imageBuffer.get()) {
        return;
    }
#else
    ASSERT(imageBuffer.get());
#endif
    
    // Fill with the gradient.
    GraphicsContext* graphicsContext = imageBuffer->context();
    graphicsContext->fillRect(FloatRect(FloatPoint(), m_size), *m_generator.get());
    
    // Grab the final image from the image buffer.
    Image* bitmap = imageBuffer->image();
    
    // Now just call drawTiled on that image.
    bitmap->drawPattern(context, srcRect, patternTransform, phase, styleColorSpace, compositeOp, destRect);
}

}
