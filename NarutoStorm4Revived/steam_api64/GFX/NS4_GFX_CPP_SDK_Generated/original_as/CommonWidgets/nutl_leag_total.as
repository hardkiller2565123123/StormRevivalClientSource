package script.freebtl_leag
{
   import flash.display.DisplayObject;
   import flash.display.DisplayObjectContainer;
   import flash.display.MovieClip;
   import flash.events.Event;
   import flash.external.*;
   import flash.geom.*;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol14")]
   public class nutl_leag_total extends MovieClip
   {
      
      internal static const STATE_IN:* = 0;
      
      internal static const STATE_LOOP:* = 1;
      
      internal static const STATE_OUT:* = 2;
      
      internal static const SUB_STATE_NONE:* = 0;
      
      internal static const SUB_STATE_CNT:* = 1;
      
      public var all_list_total_00:nut_list_total_00;
      
      public var all_list_total_01:nut_list_total_00;
      
      public var all_list_total_02:nut_list_total_00;
      
      public var all_list_total_03:nut_list_total_00;
      
      private var m_state:int;
      
      private var m_list:Array = new Array(all_nut.ENTRY_MAX);
      
      public function nutl_leag_total()
      {
         super();
         addFrameScript(5,this.frame6,10,this.frame11);
         this.m_state = STATE_IN;
         var _loc1_:int = 0;
         while(_loc1_ < this.m_list.length)
         {
            this.m_list[_loc1_] = new Object();
            this.m_list[_loc1_].SubState = SUB_STATE_NONE;
            this.m_list[_loc1_].Point = 0;
            this.m_list[_loc1_].Max = 0;
            _loc1_++;
         }
      }
      
      public function Initialize(param1:Array) : void
      {
         var _loc2_:int = 0;
         if(param1.length == all_nut.ENTRY_MAX)
         {
            _loc2_ = 0;
            while(_loc2_ < param1.length)
            {
               this.SetTotalPoint(_loc2_,param1[_loc2_]);
               this.m_list[_loc2_].Max = param1[_loc2_];
               _loc2_++;
            }
         }
         gotoAndPlay(0);
         addEventListener(Event.ENTER_FRAME,this.onEnterFrameCtrl);
      }
      
      public function onEnterFrameCtrl(param1:*) : void
      {
         var _loc2_:int = 0;
         switch(this.m_state)
         {
            case STATE_IN:
               if(currentFrameLabel == "loop")
               {
                  this.m_state = STATE_LOOP;
               }
               break;
            case STATE_LOOP:
               _loc2_ = 0;
               while(_loc2_ < this.m_list.length)
               {
                  if(this.m_list[_loc2_].SubState == SUB_STATE_CNT)
                  {
                     if(this.m_list[_loc2_].Point >= this.m_list[_loc2_].Max)
                     {
                        this.m_list[_loc2_].SubState = SUB_STATE_NONE;
                        this.SetTotalPoint(_loc2_,this.m_list[_loc2_].Max);
                     }
                     else
                     {
                        this.SetTotalPoint(_loc2_,this.m_list[_loc2_].Point);
                        ++this.m_list[_loc2_].Point;
                     }
                  }
                  _loc2_++;
               }
               break;
            case STATE_OUT:
         }
      }
      
      public function PlayCntAnm(param1:int, param2:int) : void
      {
         if(param1 >= 0 && param1 < this.m_list.length)
         {
            this.m_list[param1].SubState = SUB_STATE_CNT;
            this.m_list[param1].Point = this.m_list[param1].Max;
            this.m_list[param1].Max += param2;
         }
      }
      
      public function IsEndCntAnm(param1:int) : Boolean
      {
         if(param1 >= 0 && param1 < this.m_list.length)
         {
            return this.m_list[param1].SubState == SUB_STATE_NONE;
         }
         return false;
      }
      
      private function SetTotalPoint(param1:int, param2:int) : void
      {
         var _loc3_:nut_list_total_00 = null;
         if(param1 >= 0 && param1 < all_nut.ENTRY_MAX)
         {
            _loc3_ = this.GetNumberObject(param1);
            if(_loc3_ != null)
            {
               _loc3_.txt_score.SetText("" + param2);
            }
         }
      }
      
      private function GetNumberObject(param1:int) : nut_list_total_00
      {
         var _loc2_:nut_list_total_00 = null;
         if(param1 >= 0 && param1 < all_nut.ENTRY_MAX)
         {
            _loc2_ = nut_list_total_00(getChildByName("all_list_total_0" + param1));
         }
         return _loc2_;
      }
      
      private function GetDigit(param1:int) : int
      {
         var _loc2_:* = 1;
         while(param1 >= 10)
         {
            _loc2_++;
            param1 /= 10;
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
            param1 /= 10;
            _loc4_++;
         }
         return _loc3_;
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
      
      internal function frame6() : *
      {
         stop();
      }
      
      internal function frame11() : *
      {
         stop();
      }
   }
}

