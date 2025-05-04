//cauta in CItem
bool AddToGround(long lMapIndex, const PIXEL_POSITION& pos, bool skipOwnerCheck = false);

//adauga sub
#ifdef __OWNER_ONLY_VISIBLE_DROPS__
private:
	DWORD m_dwDropOwnerPID; // pid ul jucatorului care a dropat
public:
	void SetDropOwner(DWORD pid) { m_dwDropOwnerPID = pid; }
	DWORD GetDropOwner() const { return m_dwDropOwnerPID; }
	bool IsVisibleTo(LPCHARACTER ch) const;
#endif