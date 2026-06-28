package script.freebtl_leag
{
   import flash.display.DisplayObject;
   import flash.display.DisplayObjectContainer;
   import flash.display.MovieClip;
   import flash.events.Event;
   import flash.external.*;
   import script.xcmn_tex00.nut_tex00;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol8")]
   public class nut_round_pick1 extends MovieClip
   {
      
      internal static const LOOP_CNT_FRAME:* = 30;
      
      public var all_pick1:nut_pick1;
      
      public var mc_dmy:nut_tex00;
      
      private var m_loopCnt:int;
      
      private var m_iconCursorCtn:Array = new Array();
      
      public function nut_round_pick1()
      {
         super();
         addFrameScript(5,this.frame6,10,this.frame11);
         this.m_loopCnt = 0;
      }
      
      public function Initialize() : void
      {
         gotoAndStop(0);
         addEventListener(Event.ENTER_FRAME,this.onEnterFrameCtrl);
      }
      
      public function onEnterFrameCtrl(param1:*) : void
      {
         if(currentFrameLabel == "loop")
         {
            ++this.m_loopCnt;
            if(this.m_loopCnt > LOOP_CNT_FRAME)
            {
               gotoAndPlay("out");
            }
         }
      }
      
      public function PlayAnm(param1:Array, param2:Boolean) : void
      {
         var _loc4_:int = 0;
         var _loc5_:int = 0;
         var _loc6_:* = undefined;
         var _loc7_:* = undefined;
         var _loc8_:* = undefined;
         var _loc9_:smb_list_mark_frame_1 = null;
         var _loc3_:int = 0;
         while(_loc3_ < this.m_iconCursorCtn.length)
         {
            this.mc_dmy.removeChild(this.m_iconCursorCtn[_loc3_]);
            _loc3_++;
         }
         this.m_iconCursorCtn.length = 0;
         _loc3_ = 0;
         while(_loc3_ < param1.length)
         {
            _loc4_ = int(param1[_loc3_].Player1);
            _loc5_ = int(param1[_loc3_].Player2);
            if(_loc4_ >= 0 && _loc4_ < all_nut.ENTRY_MAX && _loc5_ >= 0 && _loc5_ < all_nut.ENTRY_MAX)
            {
               visible = true;
               this.all_pick1.visible = true;
               this.all_pick1.alpha = 1;
               _loc6_ = 0;
               while(_loc6_ < all_nut.ENTRY_MAX)
               {
                  _loc7_ = this.all_pick1.getChildByName("mc_pick1_player_" + (_loc6_ + 1));
                  if(_loc6_ == _loc4_ || _loc6_ == _loc5_)
                  {
                     if(_loc7_ != null)
                     {
                        _loc7_.visible = true;
                        if(param2 == false)
                        {
                           _loc8_ = _loc6_ == _loc4_ ? _loc5_ : _loc4_;
                           _loc9_ = new smb_list_mark_frame_1();
                           this.mc_dmy.addChild(_loc9_);
                           _loc9_.gotoAndStop("p" + (_loc8_ + 1));
                           _loc9_.x = 0;
                           _loc9_.y = _loc7_.y;
                           this.m_iconCursorCtn.push(_loc9_);
                        }
                     }
                  }
                  else if(_loc7_ != null)
                  {
                     _loc7_.visible = false;
                  }
                  _loc6_++;
               }
            }
            _loc3_++;
         }
         this.m_loopCnt = 0;
         gotoAndPlay("in");
      }
      
      public function IsEndAnm() : Boolean
      {
         return currentFrameLabel == "end";
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

