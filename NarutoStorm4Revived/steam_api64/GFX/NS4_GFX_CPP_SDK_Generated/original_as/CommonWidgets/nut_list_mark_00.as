package script.freebtl_leag
{
   import flash.display.DisplayObject;
   import flash.display.DisplayObjectContainer;
   import flash.display.MovieClip;
   import flash.events.Event;
   import flash.external.*;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol18")]
   public class nut_list_mark_00 extends MovieClip
   {
      
      internal static const STATE_NONE:* = 0;
      
      internal static const STATE_WIN_UPDATE:* = 1;
      
      internal static const STATE_LOSE_UPDATE:* = 2;
      
      internal static const STATE_POINT_IN_UPDATE:* = 3;
      
      internal static const STATE_POINT_CNT_UPDATE:* = 4;
      
      internal static const STATE_END:* = 100;
      
      internal static const SE_book:int = 0;
      
      internal static const SE_cutin_support:int = 1;
      
      internal static const SE_menu_err:int = 18;
      
      internal static const SE_menu_modeSlct:int = 22;
      
      internal static const SE_money:int = 25;
      
      internal static const SE_money2:int = 26;
      
      internal static const SE_tensionMax:int = 31;
      
      internal static const SE_catch_start:int = 35;
      
      public var mc_list_mark_score:MovieClip;
      
      public var mc_round:MovieClip;
      
      private var m_state:int;
      
      private var m_point:int;
      
      private var m_cnt:int;
      
      private var m_prevFrame:int;
      
      public function nut_list_mark_00()
      {
         super();
         addFrameScript(0,this.frame1,7,this.frame8,10,this.frame11,17,this.frame18);
         this.m_state = STATE_NONE;
         this.m_point = 0;
         this.m_cnt = 0;
         this.m_prevFrame = 0;
      }
      
      public function Initialize() : void
      {
         gotoAndStop(0);
         addEventListener(Event.ENTER_FRAME,this.onEnterFrameCtrl);
      }
      
      public function onEnterFrameCtrl(param1:*) : void
      {
         switch(this.m_state)
         {
            case STATE_NONE:
            case STATE_WIN_UPDATE:
            case STATE_LOSE_UPDATE:
               break;
            case STATE_POINT_IN_UPDATE:
               if(currentFrame == this.m_prevFrame)
               {
                  this.m_cnt = 1;
                  this.m_state = STATE_POINT_CNT_UPDATE;
               }
               this.m_prevFrame = currentFrame;
               break;
            case STATE_POINT_CNT_UPDATE:
               if(this.m_cnt > this.m_point)
               {
                  this.m_state = STATE_END;
               }
               else
               {
                  this.mc_list_mark_score.txt_list_score.SetText("+" + this.m_cnt);
                  ++this.m_cnt;
                  ExternalInterface.call("RequestPlaySE",SE_money);
                  trace("nut_list_mark_00 STATE_POINT_CNT_UPDATE");
               }
               break;
            case STATE_END:
         }
      }
      
      public function PlayWinAnm() : void
      {
         gotoAndPlay("win_in");
         this.m_state = STATE_WIN_UPDATE;
      }
      
      public function IsEndWinAnm() : Boolean
      {
         return currentFrameLabel == "win_loop";
      }
      
      public function PlayPointCntAnm(param1:int) : void
      {
         gotoAndPlay("win_point");
         this.m_point = param1;
         this.m_state = STATE_POINT_IN_UPDATE;
      }
      
      public function IsEndPointCntAnm() : Boolean
      {
         return this.m_state == STATE_END;
      }
      
      public function SetPoint(param1:int) : void
      {
         this.m_point = param1;
         gotoAndPlay("win_point");
         this.mc_list_mark_score.txt_list_score.SetText("+" + this.m_point);
         this.m_state = STATE_END;
      }
      
      public function PlayLoseAnm() : void
      {
         gotoAndPlay("lose_in");
         this.m_state = STATE_LOSE_UPDATE;
      }
      
      public function IsEndLoseAnm() : Boolean
      {
         return currentFrameLabel == "lose_loop";
      }
      
      public function SetLose() : void
      {
         gotoAndStop("lose_loop");
      }
      
      private function dbgShowChildren(param1:*, param2:int = 0) : void
      {
         var _loc4_:DisplayObject = null;
         var _loc5_:String = null;
         var _loc6_:int = 0;
         if(param2 == 0)
         {
            if(param1 is DisplayObjectContainer)
            {
               trace("DisplayObjectContainer : " + param1.name,param1);
            }
            else
            {
               trace("DisplayObject : " + param1.name,param1);
            }
            param2 = 1;
         }
         var _loc3_:uint = 0;
         while(_loc3_ < param1.numChildren)
         {
            _loc4_ = param1.getChildAt(_loc3_);
            _loc5_ = "";
            _loc6_ = 0;
            while(_loc6_ < param2)
            {
               _loc5_ += " ";
               _loc6_++;
            }
            if(_loc4_ is DisplayObjectContainer)
            {
               trace(_loc5_ + "DisplayObjectContainer : " + _loc4_.name,_loc4_);
               this.dbgShowChildren(_loc4_,param2 + 1);
            }
            else
            {
               trace(_loc5_ + "DisplayObject : " + _loc4_.name,_loc4_);
            }
            _loc3_++;
         }
      }
      
      internal function frame1() : *
      {
         stop();
      }
      
      internal function frame8() : *
      {
         stop();
      }
      
      internal function frame11() : *
      {
         stop();
      }
      
      internal function frame18() : *
      {
         stop();
      }
   }
}

