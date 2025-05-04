//cauta functia
void CItem::EncodeInsertPacket(LPENTITY ent)

//sub
	pack.bHeader = HEADER_GC_ITEM_GROUND_ADD;
	pack.x = c_pos.x;
	pack.y = c_pos.y;
	pack.z = c_pos.z;
	pack.dwVnum = GetVnum();
	pack.dwVID = m_dwVID;
	
//adauga
	LPCHARACTER ch = (LPCHARACTER)ent;

#ifdef __OWNER_ONLY_VISIBLE_DROPS__
	if (!IsVisibleTo(ch))
		return;
#endif



//adauga la final
#ifdef __OWNER_ONLY_VISIBLE_DROPS__
bool CItem::IsVisibleTo(LPCHARACTER ch) const
{
	if (!ch) 
		return false;
        
	if (ch->IsGM())
		return true;
        
    // daca nu are owner e vizibil pentru toti
	if (m_dwDropOwnerPID == 0)
		return true;
        
    // doar owner vede
	return ch->GetPlayerID() == m_dwDropOwnerPID;
}
#endif