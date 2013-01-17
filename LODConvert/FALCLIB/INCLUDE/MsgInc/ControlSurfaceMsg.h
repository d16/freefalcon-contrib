/*
 * Machine Generated include file for message "Control Surface Msg".
 * NOTE: This file is read only. DO NOT ATTEMPT TO MODIFY IT BY HAND.
 * Generated on 01-April-1997 at 18:57:03
 * Generated from file EVENTS.XLS by Kevin Klemmick
 */

#ifndef _CONTROLSURFACEMSG_H
#define _CONTROLSURFACEMSG_H

/*
 * Required Include Files
 */
#include "F4vu.h"
#include "mission.h"
#include "..\..\..\sim\include\simmover.h"

#pragma pack (1)

/*
 * Message Type Control Surface Msg
 */
class FalconControlSurfaceMsg : public FalconEvent
{
   public:
      FalconControlSurfaceMsg(VU_ID entityId, VuTargetEntity *target, VU_BOOL loopback=TRUE);
      FalconControlSurfaceMsg(VU_MSG_TYPE type, VU_ID senderid, VU_ID target);
      ~FalconControlSurfaceMsg(void);
      int Size (void) { return sizeof(dataBlock) +
         sizeof (float) * dataBlock.numDofs +
         sizeof (int) * dataBlock.numDofs +
         sizeof (int) * dataBlock.numSwitches +
         sizeof (SimBaseSpecialData) +
         FalconEvent::Size();};
      int Decode (VU_BYTE **buf, int length)
         {
         int size;

            size = FalconEvent::Decode (buf, length);
            memcpy (&dataBlock, *buf, sizeof (dataBlock));
            *buf += sizeof (dataBlock);
            size += sizeof (dataBlock);
            dataBlock.DOFData = (float*)(*buf);
            *buf += sizeof (float) * dataBlock.numDofs;
            size += sizeof (float) * dataBlock.numDofs;
            dataBlock.DOFType = (int*)(*buf);
            *buf += sizeof (int) * dataBlock.numDofs;
            size += sizeof (int) * dataBlock.numDofs;
            dataBlock.switchData = (int*)(*buf);
            *buf += sizeof (int) * dataBlock.numSwitches;
            size += sizeof (int) * dataBlock.numSwitches;
            dataBlock.specialData = (SimBaseSpecialData*)(*buf);
            *buf += sizeof (SimBaseSpecialData);
            size += sizeof (SimBaseSpecialData);

            // Handle the data before it goes away
            SimMoverClass* theEntity;
            int wasDead;

               theEntity = (SimMoverClass*)(vuDatabase->Find (dataBlock.entityID));
               if (theEntity && !theEntity->IsLocal())
               {
                  theEntity->SetDOFs (dataBlock.DOFData);
                  theEntity->SetSwitches (dataBlock.switchData);
                  wasDead = theEntity->IsDead();
                  memcpy (theEntity->SpecialData(), dataBlock.specialData, sizeof (SimBaseSpecialData));
                  if (theEntity->IsDead() && !wasDead)
                     theEntity->SetDead(TRUE);
               }
            return size;
         };
      int Encode (VU_BYTE **buf)
         {
         int size;

            size = FalconEvent::Encode (buf);
            memcpy (*buf, &dataBlock, sizeof (dataBlock));
            *buf += sizeof (dataBlock);
            size += sizeof (dataBlock);
            memcpy (*buf, dataBlock.DOFData, sizeof (float) * dataBlock.numDofs);
            *buf += sizeof (float) * dataBlock.numDofs;
            size += sizeof (float) * dataBlock.numDofs;
            memcpy (*buf, dataBlock.DOFType, sizeof (int) * dataBlock.numDofs);
            *buf += sizeof (int) * dataBlock.numDofs;
            size += sizeof (int) * dataBlock.numDofs;
            memcpy (*buf, dataBlock.switchData, sizeof (int) * dataBlock.numSwitches);
            *buf += sizeof (int) * dataBlock.numSwitches;
            size += sizeof (int) * dataBlock.numSwitches;
            memcpy (*buf, dataBlock.specialData, sizeof (SimBaseSpecialData));
            *buf += sizeof (SimBaseSpecialData);
            size += sizeof (SimBaseSpecialData);
            return size;
         };
      class DATA_BLOCK
      {
         public:
            VU_ID entityID;
            int numDofs;
            int numSwitches;
            float* DOFData;
            int* DOFType;
            int* switchData;
            SimBaseSpecialData* specialData;
      } dataBlock;

   protected:
      int Process(uchar autodisp);
};

#pragma pack ()

#endif
