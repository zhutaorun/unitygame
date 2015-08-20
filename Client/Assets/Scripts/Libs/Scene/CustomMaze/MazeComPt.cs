﻿namespace SDK.Lib
{
    public class MazeComPt : MazePtBase
    {
        public MazeComPt()
            : base(eMazePtType.eCom)
        {

        }

        override public void moveToDestPos(MazePlayer mazePlayer_)
        {
            base.moveToDestPos(mazePlayer_);
            mazePlayer_.mazePlayerTrackAniControl.moveToDestPos(this);
        }

        override public MazePtBase clone()
        {
            MazeComPt pt = new MazeComPt();
            pt.copyFrom(this);
            return pt;
        }

        override public void copyFrom(MazePtBase rh)
        {
            base.copyFrom(rh);
        }
    }
}