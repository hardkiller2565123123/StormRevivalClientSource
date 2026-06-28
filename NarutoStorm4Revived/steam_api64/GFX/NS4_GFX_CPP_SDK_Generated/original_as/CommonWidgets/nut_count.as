package script.duel_boss4
{
   import flash.display.MovieClip;
   import flash.events.Event;
   import flash.external.*;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol3")]
   public class nut_count extends MovieClip
   {
      
      internal static const STATE_OFF:* = 1;
      
      internal static const STATE_DRAW:* = 1;
      
      public var mc_msg:MovieClip;
      
      public var mc_msg_eff:MovieClip;
      
      public var mc_num:MovieClip;
      
      public var mc_num_eff:MovieClip;
      
      public var End:Function;
      
      internal var m_killCount:int;
      
      internal var m_addNum:uint;
      
      internal var m_state:int;
      
      public function nut_count()
      {
         super();
         addFrameScript(39,this.frame40,43,this.frame44,46,this.frame47,75,this.frame76,108,this.frame109,123,this.frame124);
         this.m_addNum = 0;
         this.m_killCount = 0;
         this.mc_num.gotoAndStop("num_1");
         this.mc_msg.gotoAndStop("num_1");
         this.m_state = STATE_OFF;
      }
      
      public function Initialize(param1:int) : *
      {
         if(param1 != 0)
         {
            this.mc_msg.mc_msg_l.gotoAndStop("msg2");
            this.mc_msg.mc_msg_r.gotoAndStop("msg2");
         }
         addEventListener(Event.ENTER_FRAME,this.OnUpdate);
      }
      
      public function OnUpdate() : *
      {
         var _loc1_:int = 0;
         var _loc2_:int = 0;
         var _loc3_:int = 0;
         var _loc4_:MovieClip = null;
         var _loc5_:int = 0;
         var _loc6_:MovieClip = null;
         if(this.m_addNum > 0 && this.m_killCount < 999999)
         {
            if(this.m_addNum > 50)
            {
               this.m_killCount += this.m_addNum - 50;
               this.m_addNum = 50;
            }
            else
            {
               ++this.m_killCount;
               --this.m_addNum;
            }
            if(this.m_killCount > 999999)
            {
               this.m_killCount = 999999;
               this.m_addNum = 0;
            }
            if(this.m_killCount >= 100000)
            {
               this.mc_num.gotoAndStop("num_100000");
               this.mc_msg.gotoAndStop("num_100000");
            }
            else if(this.m_killCount >= 10000)
            {
               this.mc_num.gotoAndStop("num_10000");
               this.mc_msg.gotoAndStop("num_10000");
            }
            else if(this.m_killCount >= 1000)
            {
               this.mc_num.gotoAndStop("num_1000");
               this.mc_msg.gotoAndStop("num_1000");
            }
            else if(this.m_killCount >= 100)
            {
               this.mc_num.gotoAndStop("num_100");
               this.mc_msg.gotoAndStop("num_100");
            }
            else if(this.m_killCount >= 10)
            {
               this.mc_num.gotoAndStop("num_10");
               this.mc_msg.gotoAndStop("num_10");
            }
            if(this.mc_msg_eff)
            {
               if(this.mc_msg_eff.mc_msg_l)
               {
                  this.mc_msg_eff.mc_msg_l = null;
               }
            }
            _loc1_ = this.m_killCount;
            _loc2_ = 0;
            _loc3_ = 100000;
            _loc5_ = 0;
            while(_loc5_ < 6)
            {
               _loc4_ = MovieClip(this.mc_num.getChildByName("mc_num" + _loc3_));
               if(_loc4_)
               {
                  _loc2_ = _loc1_ / _loc3_;
                  _loc4_.gotoAndStop("num_" + _loc2_);
                  _loc1_ -= _loc2_ * _loc3_;
               }
               if(this.mc_num_eff)
               {
                  _loc6_ = MovieClip(this.mc_num_eff.getChildByName("mc_num" + _loc3_));
                  if(_loc4_)
                  {
                     if(_loc6_)
                     {
                        _loc6_.gotoAndStop("num_" + _loc2_);
                        _loc6_.visible = true;
                     }
                  }
                  else if(_loc6_)
                  {
                     _loc6_.visible = false;
                  }
               }
               _loc3_ /= 10;
               _loc5_++;
            }
         }
      }
      
      public function AddNum(param1:uint) : *
      {
         if(this.m_state == STATE_OFF)
         {
            this.m_state = STATE_DRAW;
         }
         this.m_addNum += param1;
         var _loc2_:int = this.m_killCount + this.m_addNum;
         if(_loc2_ >= 100000)
         {
            gotoAndPlay("5_in");
         }
         else if(_loc2_ >= 10000)
         {
            gotoAndPlay("4_in");
         }
         else if(_loc2_ >= 1000)
         {
            gotoAndPlay("3_in");
         }
         else if(_loc2_ >= 100)
         {
            gotoAndPlay("2_in");
         }
      }
      
      internal function frame40() : *
      {
         this.stop();
      }
      
      internal function frame44() : *
      {
         this.stop();
      }
      
      internal function frame47() : *
      {
         this.stop();
      }
      
      internal function frame76() : *
      {
         gotoAndPlay("4_loop");
      }
      
      internal function frame109() : *
      {
         gotoAndPlay("5_loop");
      }
      
      internal function frame124() : *
      {
         this.stop();
      }
   }
}

