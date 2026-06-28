package script.msg_wins_m
{
   import SeIdList.SeId;
   import flash.display.MovieClip;
   import flash.events.Event;
   import flash.external.ExternalInterface;
   import script.msg_wins_txt.nut_wins;
   import script.num_l.nut_num_l;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol8")]
   public class nut_wins_m extends MovieClip
   {
      
      internal static const DISP_WAIT:int = 30;
      
      internal static const MOVE_TYPE_NORMAL:int = 0;
      
      internal static const MOVE_TYPE_ULTIMATE:int = 1;
      
      public var all_wins:nut_wins;
      
      internal var m_end:Boolean = false;
      
      internal var m_count:int = 0;
      
      internal var m_moveType:int = 0;
      
      internal var m_isRequest:Boolean = false;
      
      public var SetClosed:Function;
      
      public var RequestReward:Function;
      
      public function nut_wins_m()
      {
         super();
         addFrameScript(25,this.frame26);
      }
      
      public function nut_wins_l() : *
      {
      }
      
      public function Initialize() : *
      {
         ExternalInterface.call("RequestPlaySE",SeId.CCD_SE_ID_MENU_MODE_FIX);
         addEventListener(Event.ENTER_FRAME,this.onEnterFrameCtrl);
      }
      
      public function SetMoveType(param1:int) : *
      {
         this.m_moveType = param1;
      }
      
      public function onEnterFrameCtrl(param1:*) : void
      {
         if("loop" == this.currentFrameLabel)
         {
            if(this.m_count > DISP_WAIT)
            {
               if(this.m_moveType == MOVE_TYPE_ULTIMATE)
               {
                  if(!this.m_isRequest)
                  {
                     this.m_isRequest = true;
                     this.RequestReward();
                  }
               }
               else
               {
                  gotoAndPlay("out");
               }
            }
            else
            {
               ++this.m_count;
            }
         }
         if(this.totalFrames <= this.currentFrame)
         {
            this.m_end = true;
            stop();
            this.SetClosed();
         }
      }
      
      public function GetMode() : Boolean
      {
         return this.m_end;
      }
      
      public function SetStop() : *
      {
         stop();
      }
      
      public function SetStart() : *
      {
         this.m_end = false;
         gotoAndPlay("in");
      }
      
      public function SetOut() : *
      {
         gotoAndPlay("out");
      }
      
      public function SetWin(param1:int) : void
      {
         var _loc2_:int = 0;
         var _loc3_:int = 0;
         var _loc4_:int = 0;
         if(param1 >= 100)
         {
            _loc2_ = param1 / 100;
         }
         if(param1 >= 10)
         {
            _loc3_ = (param1 - _loc2_ * 100) / 10;
         }
         _loc4_ = param1 - _loc2_ * 100 - _loc3_ * 10;
         trace("value:" + _loc2_);
         trace("value:" + _loc3_);
         trace("value:" + _loc4_);
         var _loc5_:nut_num_l = this.all_wins.getChildByName("mc_num100") as nut_num_l;
         var _loc6_:nut_num_l = this.all_wins.getChildByName("mc_num10") as nut_num_l;
         var _loc7_:nut_num_l = this.all_wins.getChildByName("mc_num1") as nut_num_l;
         trace(_loc5_);
         trace(_loc6_);
         trace(_loc7_);
         if(_loc2_ > 0)
         {
            this.all_wins.gotoAndStop("match_100");
            trace("test");
            _loc5_.Set(_loc2_);
            _loc6_.Set(_loc3_);
            _loc7_.Set(_loc4_);
         }
         else if(_loc3_ > 0)
         {
            this.all_wins.gotoAndStop("match_10");
            _loc6_.Set(_loc3_);
            _loc7_.Set(_loc4_);
         }
         else
         {
            this.all_wins.gotoAndStop("match_1");
            _loc7_.Set(_loc4_);
         }
      }
      
      internal function frame26() : *
      {
         stop();
      }
   }
}

