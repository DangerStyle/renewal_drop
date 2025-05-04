//cauta
SECTREE::InsertEntity(LPENTITY pkEnt)

//in functie cauta
	if (m_set_entity.find(pkEnt) != m_set_entity.end())
	{
		sys_err("entity %p already exist in this sectree!", get_pointer(pkEnt));
		return false;
	}

// adauga sub
#ifdef __OWNER_ONLY_VISIBLE_DROPS__
    if (entity->IsType(ENTITY_ITEM))
    {
        LPITEM item = (LPITEM)entity;
        if (item->GetDropOwner() != 0)
        {
            // trimis individual prin EncodeInsertPacket
            return;
        }
    }
#endif


//asa
bool SECTREE::InsertEntity(LPENTITY pkEnt)
{
	LPSECTREE pkCurTree;

	if ((pkCurTree = pkEnt->GetSectree()) == this)
		return false;

	if (m_set_entity.find(pkEnt) != m_set_entity.end())
	{
		sys_err("entity %p already exist in this sectree!", get_pointer(pkEnt));
		return false;
	}

#ifdef __OWNER_ONLY_VISIBLE_DROPS__
    if (entity->IsType(ENTITY_ITEM))
    {
        LPITEM item = (LPITEM)entity;
        if (item->GetDropOwner() != 0)
        {
            // trimis individual prin EncodeInsertPacket
            return;
        }
    }
#endif

	if (pkCurTree)
		pkCurTree->m_set_entity.erase(pkEnt);

	pkEnt->SetSectree(this);
	//pkEnt->UpdateSectree();

	m_set_entity.insert(pkEnt);

	if (pkEnt->IsType(ENTITY_CHARACTER))
	{
		LPCHARACTER pkChr = (LPCHARACTER)pkEnt;

		if (pkChr->IsPC())
		{
			IncreasePC();

			if (pkCurTree)
				pkCurTree->DecreasePC();
		}
		else if (m_iPCCount > 0 && !pkChr->IsWarp() && !pkChr->IsGoto()) // PC가 아니고 이 곳에 PC가 있다면 Idle event를 시작 시킨다.
		{
			pkChr->StartStateMachine();
		}
	}

	return true;
}