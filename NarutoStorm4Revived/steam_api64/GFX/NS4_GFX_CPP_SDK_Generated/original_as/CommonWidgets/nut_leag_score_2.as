package script.freebtl_leag
{
   import flash.display.DisplayObject;
   import flash.display.DisplayObjectContainer;
   import flash.display.MovieClip;
   import flash.events.Event;
   import flash.external.*;
   import script.freebtl_namebar.nut_namebar01;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol5")]
   public class nut_leag_score extends MovieClip
   {
      
      internal static const STATE_IN:* = 0;
      
      internal static const STATE_OUT:* = 1;
      
      internal static const STATE_END:* = 2;
      
      internal static const STATE_WIN_POINT_ENTER:* = 10;
      
      internal static const STATE_WIN_POINT_UPDATE:* = 11;
      
      internal static const STATE_WIN_POINT_CNT_ENTER:* = 20;
      
      internal static const STATE_WIN_POINT_CNT_UPDATE:* = 21;
      
      internal static const STATE_WIN_POINT_CNT_WAIT:* = 22;
      
      internal static const STATE_BONUS_POINT_ENTER:* = 30;
      
      internal static const STATE_BONUS_POINT_UPDATE:* = 31;
      
      internal static const STATE_BONUS_POINT_CNT_ENTER:* = 40;
      
      internal static const STATE_BONUS_POINT_CNT_UPDATE:* = 41;
      
      internal static const STATE_BONUS_POINT_CNT_WAIT:* = 42;
      
      internal static const STATE_TOTAL_POINT_ENTER:* = 50;
      
      internal static const STATE_TOTAL_POINT_UPDATE:* = 51;
      
      internal static const STATE_TOTAL_POINT_CNT_ENTER:* = 60;
      
      internal static const STATE_TOTAL_POINT_CNT_UPDATE:* = 61;
      
      internal static const STATE_TOTAL_POINT_CNT_WAIT:* = 62;
      
      internal static const WIN_POINT_WAIT_FRAME:* = 8;
      
      internal static const BONUS_POINT_WAIT_FRAME:* = 8;
      
      internal static const TOTAL_POINT_WAIT_FRAME:* = 8;
      
      internal static const CLOSE_WAIT_FRAME:* = 90;
      
      internal static const SE_book:int = 0;
      
      internal static const SE_cutin_support:int = 1;
      
      internal static const SE_menu_err:int = 18;
      
      internal static const SE_menu_modeSlct:int = 22;
      
      internal static const SE_money:int = 25;
      
      internal static const SE_money2:int = 26;
      
      internal static const SE_tensionMax:int = 31;
      
      internal static const SE_catch_start:int = 35;
      
      public var mc_score_base:MovieClip;
      
      public var mc_score_namebar:nut_namebar01;
      
      public var mc_score_total:nut_txt_score_total;
      
      private var m_charaFace:String;
      
      private var m_charaName:String;
      
      private var m_playerNum:int;
      
      private var m_point:int;
      
      private var m_bonus:int;
      
      private var m_total:int;
      
      private var m_state:int;
      
      private var m_waitCnt:*;
      
      public function nut_leag_score()
      {
         super();
         addFrameScript(14,this.frame15,24,this.frame25);
         this.m_charaFace = "";
         this.m_charaName = "";
         this.m_playerNum = 0;
         this.m_point = 0;
         this.m_bonus = 0;
         this.m_total = 0;
         this.m_state = STATE_END;
         this.m_waitCnt = 0;
      }
      
      public function Initialize() : void
      {
         visible = false;
         addEventListener(Event.ENTER_FRAME,this.onEnterFrameCtrl);
      }
      
      public function RequestPlay(param1:String, param2:String, param3:int, param4:int, param5:int, param6:Boolean) : void
      {
         visible = true;
         this.m_charaFace = param1;
         this.m_charaName = param2;
         this.m_playerNum = param3;
         this.m_point = param4;
         this.m_bonus = param5;
         this.m_total = this.m_point + this.m_bonus;
         this.mc_score_base.txt_win_title.SetText(ExternalInterface.call("MessageConvert","league_015"));
         this.mc_score_base.txt_score_title00.SetText(ExternalInterface.call("MessageConvert","league_016"));
         this.mc_score_base.txt_score_title01.SetText(ExternalInterface.call("MessageConvert","league_017"));
         this.mc_score_base.txt_score.SetText(ExternalInterface.call("MessageConvert","league_018"));
         this.mc_score_base.txt_score_point00.SetText("0");
         this.mc_score_base.txt_score_point01.SetText("0");
         this.mc_score_base.txt_score_title01.visible = false;
         this.mc_score_base.txt_score.visible = false;
         this.mc_score_base.txt_score_point00.visible = false;
         this.mc_score_base.txt_score_point01.visible = false;
         this.mc_score_total.visible = false;
         if(param6)
         {
            this.mc_score_namebar.setSelect(false,false);
            this.mc_score_namebar.setDispFace(true);
            this.mc_score_namebar.setPlayerIcon(all_nut.PLAYER_NUMBER[this.m_playerNum]);
            this.mc_score_namebar.setFace(this.m_charaFace);
            if(this.m_playerNum < 8)
            {
               this.mc_score_namebar.SetUserName(this.m_charaName);
            }
            else
            {
               this.mc_score_namebar.SetUserName("");
               this.mc_score_namebar.setName(this.m_charaName);
            }
         }
         else
         {
            this.mc_score_namebar.setSelect(false,false);
            this.mc_score_namebar.setDispFace(true);
            this.mc_score_namebar.setPlayerIcon(all_nut.PLAYER_NUMBER[this.m_playerNum]);
            this.mc_score_namebar.setFace(this.m_charaFace);
            this.mc_score_namebar.setName(this.m_charaName);
         }
         this.SetNextState(STATE_IN);
         gotoAndPlay(0);
      }
      
      public function onEnterFrameCtrl(param1:*) : void
      {
         var _loc2_:int = 0;
         var _loc3_:Array = null;
         var _loc4_:* = undefined;
         var _loc5_:MovieClip = null;
         var _loc6_:int = 0;
         switch(this.m_state)
         {
            case STATE_IN:
               if(currentFrameLabel == "loop")
               {
                  this.SetNextState(STATE_WIN_POINT_ENTER);
               }
               break;
            case STATE_WIN_POINT_ENTER:
               this.mc_score_base.txt_score_title00.visible = true;
               this.m_waitCnt = 0;
               this.SetNextState(STATE_WIN_POINT_UPDATE);
               break;
            case STATE_WIN_POINT_UPDATE:
               if(this.m_waitCnt >= WIN_POINT_WAIT_FRAME)
               {
                  this.SetNextState(STATE_WIN_POINT_CNT_ENTER);
               }
               ++this.m_waitCnt;
               break;
            case STATE_WIN_POINT_CNT_ENTER:
               this.mc_score_base.txt_score_point00.visible = true;
               this.m_waitCnt = 0;
               this.SetNextState(STATE_WIN_POINT_CNT_UPDATE);
               break;
            case STATE_WIN_POINT_CNT_UPDATE:
               if(this.m_waitCnt > this.m_point)
               {
                  this.m_waitCnt = 0;
                  this.SetNextState(STATE_WIN_POINT_CNT_WAIT);
                  ExternalInterface.call("RequestPlaySE",SE_money2);
               }
               else
               {
                  this.mc_score_base.txt_score_point00.SetText("" + this.m_waitCnt);
                  ++this.m_waitCnt;
                  ExternalInterface.call("RequestPlaySE",SE_money);
               }
               break;
            case STATE_WIN_POINT_CNT_WAIT:
               this.SetNextState(STATE_BONUS_POINT_ENTER);
               break;
            case STATE_BONUS_POINT_ENTER:
               this.mc_score_base.txt_score_title01.visible = true;
               this.m_waitCnt = 0;
               this.SetNextState(STATE_BONUS_POINT_UPDATE);
               break;
            case STATE_BONUS_POINT_UPDATE:
               if(this.m_waitCnt >= BONUS_POINT_WAIT_FRAME)
               {
                  this.SetNextState(STATE_BONUS_POINT_CNT_ENTER);
               }
               ++this.m_waitCnt;
               break;
            case STATE_BONUS_POINT_CNT_ENTER:
               this.mc_score_base.txt_score_point01.visible = true;
               this.m_waitCnt = 0;
               this.SetNextState(STATE_BONUS_POINT_CNT_UPDATE);
               break;
            case STATE_BONUS_POINT_CNT_UPDATE:
               if(this.m_waitCnt > this.m_bonus)
               {
                  this.m_waitCnt = 0;
                  this.SetNextState(STATE_BONUS_POINT_CNT_WAIT);
                  ExternalInterface.call("RequestPlaySE",SE_money2);
               }
               else
               {
                  this.mc_score_base.txt_score_point01.SetText("" + this.m_waitCnt);
                  ++this.m_waitCnt;
                  ExternalInterface.call("RequestPlaySE",SE_money);
               }
               break;
            case STATE_BONUS_POINT_CNT_WAIT:
               this.SetNextState(STATE_TOTAL_POINT_ENTER);
               break;
            case STATE_TOTAL_POINT_ENTER:
               this.mc_score_base.txt_score.visible = true;
               this.m_waitCnt = 0;
               this.SetNextState(STATE_TOTAL_POINT_UPDATE);
               break;
            case STATE_TOTAL_POINT_UPDATE:
               if(this.m_waitCnt >= TOTAL_POINT_WAIT_FRAME)
               {
                  this.SetNextState(STATE_TOTAL_POINT_CNT_ENTER);
               }
               ++this.m_waitCnt;
               break;
            case STATE_TOTAL_POINT_CNT_ENTER:
               this.mc_score_total.visible = true;
               this.mc_score_total.gotoAndStop("num_1");
               this.m_waitCnt = 0;
               this.SetNextState(STATE_TOTAL_POINT_CNT_UPDATE);
               break;
            case STATE_TOTAL_POINT_CNT_UPDATE:
               if(this.m_waitCnt > this.m_total)
               {
                  this.m_waitCnt = 0;
                  this.SetNextState(STATE_TOTAL_POINT_CNT_WAIT);
                  ExternalInterface.call("RequestPlaySE",SE_money2);
               }
               else
               {
                  _loc2_ = this.GetDigit(this.m_waitCnt);
                  switch(_loc2_)
                  {
                     case 1:
                        this.mc_score_total.gotoAndStop("num_1");
                        break;
                     case 2:
                        this.mc_score_total.gotoAndStop("num_10");
                        break;
                     case 3:
                        this.mc_score_total.gotoAndStop("num_100");
                  }
                  _loc3_ = ["mc_num_l_1","mc_num_l_10","mc_num_l_100"];
                  _loc4_ = 0;
                  while(_loc4_ < _loc2_)
                  {
                     _loc5_ = MovieClip(this.mc_score_total.getChildByName(_loc3_[_loc4_]));
                     if(_loc5_ != null)
                     {
                        _loc6_ = this.GetDigitNumber(this.m_waitCnt,_loc4_ + 1);
                        _loc5_.gotoAndStop("num_" + _loc6_);
                     }
                     _loc4_++;
                  }
                  ExternalInterface.call("RequestPlaySE",SE_money);
                  ++this.m_waitCnt;
               }
               break;
            case STATE_TOTAL_POINT_CNT_WAIT:
               if(this.m_waitCnt >= CLOSE_WAIT_FRAME)
               {
                  gotoAndPlay("out");
                  this.SetNextState(STATE_OUT);
               }
               else
               {
                  ++this.m_waitCnt;
               }
               break;
            case STATE_OUT:
               if(currentFrameLabel == "end")
               {
                  this.SetNextState(STATE_END);
               }
               break;
            case STATE_END:
         }
      }
      
      public function IsEndAnm() : Boolean
      {
         return this.m_state == STATE_END;
      }
      
      private function SetNextState(param1:int) : void
      {
         this.m_state = param1;
      }
      
      private function GetDigit(param1:int) : int
      {
         var _loc2_:* = 1;
         while(param1 >= 10)
         {
            ++_loc2_;
            param1 = param1 / 10;
         }
         return _loc2_;
      }
      
      private function GetDigitNumber(param1:int, param2:int) : int
      {
         var _loc3_:int = 0;
         var _loc4_:* = 0;
         while(_loc4_ < param2)
         {
            _loc3_ = param1 % 10;
            param1 = param1 / 10;
            _loc4_++;
         }
         return _loc3_;
      }
      
      public function dbgShowChildren(param1:*, param2:int = 0) : void
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
               _loc5_ = _loc5_ + " ";
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
      
      internal function frame15() : *
      {
         stop();
      }
      
      internal function frame25() : *
      {
         stop();
      }
   }
}

