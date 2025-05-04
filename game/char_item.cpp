// in functia "bool CHARACTER::DropItem"
//cauta: if (pkItemToDrop->AddToGround(GetMapIndex(), pxPos))
	//si modifica:

    if (pkItemToDrop->AddToGround(GetMapIndex(), pxPos))
    {
#ifdef __OWNER_ONLY_VISIBLE_DROPS__
        pkItemToDrop->SetDropOwner(GetPlayerID());
        
        // Trimite packet doar owner-ului
        pkItemToDrop->EncodeInsertPacket(this);
        
        ChatPacket(CHAT_TYPE_INFO, "only you can see this item");
#else
        ChatPacket(CHAT_TYPE_INFO, "3 minutes before destroy");
#endif

        if (LC_IsYMIR())
            item->AttrLog();

        pkItemToDrop->StartDestroyEvent();
        ITEM_MANAGER::instance().FlushDelayedSave(pkItemToDrop);

        char szHint[32 + 1];
        snprintf(szHint, sizeof(szHint), "%s %u %u", pkItemToDrop->GetName(), pkItemToDrop->GetCount(), pkItemToDrop->GetOriginalVnum());
        LogManager::instance().ItemLog(this, pkItemToDrop, "DROP", szHint);
    }

    return true;
}