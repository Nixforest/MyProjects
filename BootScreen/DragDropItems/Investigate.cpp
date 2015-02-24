DWORD dwEffect;
HRESULT hr = ::DoDragDrop (pdo, pds, DROPEFFECT_MOVE | DROPEFFECT_COPY, &dwEffect);

if (SUCCEEDED (hr) && dwEffect == DROPEFFECT_MOVE) 
{
	// Delete the original data from the document. 
}
HRESULT __stdcall CDropSource::QueryContinueDrag (BOOL fEscape, DWORD grfKeyState)
{
	if (fEscape)
		return DRAGDROP_S_CANCEL; 
	// Esc key was pressed. 
	if (!(grfKeyState & MK_LBUTTON))
		return DRAGDROP_S_DROP;
	// Left mouse button was released. 
	return S_OK; // Let the operation continue. 
}
HRESULT __stdcall CDropSource::GiveFeedback (DWORD dwEffect)
{
	HCURSOR hCursor;
	switch (dwEffect)
	{
		// Inspect dwEffect, and load a cursor handle in hCursor. 
	}
	::SetCursor(hCursor);
	return S_OK;
}
HRESULT __stdcall CDropSource::GiveFeedback (DWORD dwEffect)
{
	return DRAGDROP_S_USEDEFAULTCURSORS;
}
HRESULT __stdcall CDropTarget::DragEnter(IDataObject* pDataObject, DWORD grfKeyState, POINTL pt, DWORD* pdwEffect)
{
	FORMATETC fe = { CF_TEXT, NULL, DVASPECT_CONTENT, -1, TYMED_HGLOBAL }; 
	if (pDataObject->QueryGetData(&fe) == S_OK)
	{ 
		m_bCanAcceptData = TRUE;
		*pdwEffect = (grfKeyState & MK_CONTROL) ? DROPEFFECT_COPY : DROPEFFECT_MOVE;
	} 
	else
	{ 
		m_bCanAcceptData = FALSE; *pdwEffect = DROPEFFECT_NONE;
	} 
	return S_OK;
} 
HRESULT __stdcall CDropTarget::DragOver(DWORD grfKeyState, POINTL pt, DWORD* pdwEffect)
{ 
	if (m_bCanAcceptData)
		*pdwEffect = (grfKeyState & MK_CONTROL) ? DROPEFFECT_COPY : DROPEFFECT_MOVE;
	else
		*pdwEffect = DROPEFFECT_NONE; return S_OK;
}
HRESULT __stdcall CDropTarget::Drop(IDataObject* pDataObject, DWORD grfKeyState, POINTL pt, DWORD* pdwEffect)
{
	if (m_bCanAcceptData)
	{
		FORMATETC fe = { CF_TEXT, NULL, DVASPECT_CONTENT, -1, TYMED_HGLOBAL };
		STGMEDIUM stgm;
		if (SUCCEEDED(pDataObject->GetData(&fe, &stgm)) && stgm.hGlobal != NULL)
		{ 
			// Copy the string from the global memory block. . . . 
			::ReleaseStgMedium (&stgm);
			*pdwEffect = (grfKeyState & MK_CONTROL) ? DROPEFFECT_COPY : DROPEFFECT_MOVE;
			return S_OK;
		}
	} 
	// If we make it to here, the drop did not succeed.
	*pdwEffect = DROPEFFECT_NONE;
	return S_OK; 
}