/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2014 Chukong Technologies

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#ifndef __CCREF_H__
#define __CCREF_H__

/**
 * @addtogroup base_nodes
 * @{
 */

class Ref;

/** Interface that defines how to clone an Ref */
class Clonable
{
public:
	/** returns a copy of the Ref */
    virtual Clonable* clone() const = 0;
    /**
     * @js NA
     * @lua NA
     */
	virtual ~Clonable() {};

    /** returns a copy of the Ref.
     @deprecated Use clone() instead
     */
    Ref* copy() const;
};

class Ref
{
public:
    /**
     * Retains the ownership.
     *
     * This increases the Ref's reference count.
     *
     * @see release, autorelease
     * @js NA
     */
    void retain();
    
    /**
     * Release the ownership immediately.
     *
     * This decrements the Ref's reference count.
     *
     * If the reference count reaches 0 after the descrement, this Ref is
     * destructed.
     *
     * @see retain, autorelease
     * @js NA
     */
    void release();

    /**
     * Release the ownership sometime soon automatically.
     *
     * This descrements the Ref's reference count at the end of current
     * autorelease pool block.
     *
     * If the reference count reaches 0 after the descrement, this Ref is
     * destructed.
     *
     * @returns The Ref itself.
     *
     * @see AutoreleasePool, retain, release
     * @js NA
     * @lua NA
     */
    Ref* autorelease();

    /**
     * Returns the Ref's current reference count.
     *
     * @returns The Ref's reference count.
     * @js NA
     */
    unsigned int getReferenceCount() const;
    
protected:
    /**
     * Constructor
     *
     * The Ref's reference count is 1 after construction.
     * @js NA
     */
    Ref();
    
public:
    /**
     * @js NA
     * @lua NA
     */
    virtual ~Ref();
    
protected:
    /// count of references
    unsigned int _referenceCount;
    
    friend class AutoreleasePool;
};

typedef void (Ref::*SEL_CallFuncND)(void*, void*);



// end of base_nodes group
/// @}


#endif // __CCREF_H__
