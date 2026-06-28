package script.hist_cmn_brt
{
   import flash.display.MovieClip;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol25")]
   public class nut_link extends MovieClip
   {
      
      public var mc_link:MovieClip;
      
      internal const CCD_EPISODE_LINK_NUM:* = 14;
      
      internal const CCD_WAIT_TIME_MAX:* = 6;
      
      private var m_episodeLinkList:Array = new Array(this.CCD_EPISODE_LINK_NUM);
      
      private var m_curSelectLinkNo:int;
      
      private var m_oldOpenedLinkNum:int;
      
      private var m_unlockedLinkNum:int;
      
      private var m_waitTimer:int;
      
      public function nut_link()
      {
         super();
         addFrameScript(18,this.frame19,24,this.frame25);
         this.m_curSelectLinkNo = 0;
         this.m_oldOpenedLinkNum = 0;
         this.m_unlockedLinkNum = 0;
         this.m_waitTimer = 0;
      }
      
      public function Initialize(param1:int) : *
      {
         var _loc3_:String = null;
         var _loc2_:int = 0;
         while(_loc2_ < this.CCD_EPISODE_LINK_NUM)
         {
            _loc3_ = null;
            if(_loc2_ + 1 < 10)
            {
               _loc3_ = "mc_ep_0";
            }
            else
            {
               _loc3_ = "mc_ep_";
            }
            _loc3_ += String(_loc2_ + 1);
            this.m_episodeLinkList[_loc2_] = this["mc_link"][_loc3_];
            _loc2_++;
         }
         this.m_curSelectLinkNo = 0;
         this.m_oldOpenedLinkNum = param1;
      }
      
      public function StartSelectNo(param1:int) : *
      {
         this.m_curSelectLinkNo = param1;
      }
      
      public function SetUnlockEpisodeNum(param1:int) : *
      {
         trace("SetUnlockEpisodeNum unlockNum : " + param1);
         var _loc2_:int = 0;
         while(_loc2_ < this.CCD_EPISODE_LINK_NUM)
         {
            trace("SetUnlockEpisodeNum index : " + _loc2_);
            if(_loc2_ < param1)
            {
               if(this.m_oldOpenedLinkNum <= _loc2_)
               {
                  this.m_episodeLinkList[_loc2_].gotoAndPlay("rel");
                  trace("rel");
               }
               else
               {
                  this.m_episodeLinkList[_loc2_].gotoAndStop("on");
                  trace("on");
               }
            }
            else
            {
               this.m_episodeLinkList[_loc2_].gotoAndStop("off");
               trace("off");
            }
            _loc2_++;
         }
         this.m_unlockedLinkNum = param1;
      }
      
      public function StartUpdate() : *
      {
         this.m_episodeLinkList[this.m_curSelectLinkNo].gotoAndPlay("sel");
      }
      
      public function NextEpisode() : Boolean
      {
         var _loc1_:Boolean = false;
         if(this.m_waitTimer == 0 && this.m_curSelectLinkNo < this.m_unlockedLinkNum - 1)
         {
            this.m_episodeLinkList[this.m_curSelectLinkNo].gotoAndStop("on");
            ++this.m_curSelectLinkNo;
            this.m_episodeLinkList[this.m_curSelectLinkNo].gotoAndPlay("sel");
            _loc1_ = true;
            this.m_waitTimer = this.CCD_WAIT_TIME_MAX;
         }
         return _loc1_;
      }
      
      public function PrevEpisode() : Boolean
      {
         var _loc1_:Boolean = false;
         if(this.m_waitTimer == 0 && this.m_curSelectLinkNo > 0)
         {
            this.m_episodeLinkList[this.m_curSelectLinkNo].gotoAndStop("on");
            --this.m_curSelectLinkNo;
            this.m_episodeLinkList[this.m_curSelectLinkNo].gotoAndPlay("sel");
            _loc1_ = true;
            this.m_waitTimer = this.CCD_WAIT_TIME_MAX;
         }
         return _loc1_;
      }
      
      public function PlayDecideAnm() : *
      {
         this.m_episodeLinkList[this.m_curSelectLinkNo].gotoAndPlay("enter");
      }
      
      public function GetSelectLinkIndex() : int
      {
         return this.m_curSelectLinkNo;
      }
      
      public function UpdateWaitTimer() : *
      {
         if(this.m_waitTimer > 0)
         {
            --this.m_waitTimer;
         }
      }
      
      public function SetSelLoopAnm() : *
      {
         this.m_episodeLinkList[this.m_curSelectLinkNo].gotoAndPlay("sel_loop");
      }
      
      internal function frame19() : *
      {
         this.stop();
      }
      
      internal function frame25() : *
      {
         this.stop();
      }
   }
}

