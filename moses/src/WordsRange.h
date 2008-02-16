// $Id: WordsRange.h 87 2007-09-10 23:17:43Z hieu $

/***********************************************************************
Moses - factored phrase-based language decoder
Copyright (C) 2006 University of Edinburgh

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
***********************************************************************/

#pragma once

#include <iostream>
#include "TypeDef.h"
#include "Util.h"

class DecodeStep;

/***
 * Efficient version of WordsBitmap for contiguous ranges
 */
class WordsRange
{
	friend std::ostream& operator << (std::ostream& out, const WordsRange& range);

	size_t m_decodeStepId;
	size_t m_startPos, m_endPos;
public:
	inline WordsRange()
	: m_decodeStepId(NOT_FOUND)
	, m_startPos(NOT_FOUND)
	, m_endPos(NOT_FOUND)
	{}
	inline WordsRange(size_t decodeStepId, size_t startPos, size_t endPos) 
	: m_decodeStepId(decodeStepId)
	, m_startPos(startPos)
	, m_endPos(endPos) 
	{}
	inline WordsRange(const WordsRange &copy)
	 : m_decodeStepId(copy.m_decodeStepId)
	 , m_startPos(copy.GetStartPos())
	 , m_endPos(copy.GetEndPos())
	 {}

	inline size_t GetStartPos() const
	{
		return m_startPos;
	}
	inline size_t GetEndPos() const
	{
		return m_endPos;
	}
	inline size_t GetSize() const
	{
		return (m_startPos == NOT_FOUND) ? 0 : m_endPos - m_startPos + 1;
	}
	inline size_t GetDecodeStepId() const
	{
		return m_decodeStepId;
	}

	//! distortion cost when phrase is moved from prevRange to this range
	inline int CalcDistortion(const WordsRange &prevRange) const
	{
		int dist = (int)prevRange.GetEndPos() - (int)GetStartPos() + 1 ;
		return abs(dist);
	}
	//! count of words translated
	inline size_t GetNumWordsCovered() const
	{
		return (m_startPos == NOT_FOUND) ? 0 : m_endPos - m_startPos + 1;
	}

	//! transitive comparison
	inline bool operator<(const WordsRange& x) const 
	{
		return (m_startPos<x.m_startPos 
						|| (m_startPos==x.m_startPos && m_endPos<x.m_endPos));
	}
	
	// Whether two word ranges overlap or not
	inline bool Overlap(const WordsRange &x) const
	{
		
		if ( x.m_endPos < m_startPos || x.m_startPos > m_endPos
				|| m_decodeStepId != x.m_decodeStepId)
			return false;
		
		return true;
	}
	
	TO_STRING();
};

