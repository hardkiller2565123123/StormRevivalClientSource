package script.msg_wins_l
{
   import flash.display.MovieClip;
   import flash.events.Event;
   import script.num_l.nut_num_l;
   
   public class nut_wins_l extends MovieClip
   {
      
      internal var m_end:Boolean = false;
      
      public var SetClosed:Function;
      
      public function nut_wins_l()
      {
         super();
         addEventListener(Event.ENTER_FRAME,this.onEnterFrameCtrl);
      }
      
      public function onEnterFrameCtrl(param1:*) : void
      {
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
      
      public function Set(param1:int) : void
      {
         var _loc2_:int = param1 / 100;
         var _loc3_:int = (param1 - _loc2_ * 100) / 10;
         var _loc4_:int = param1 - _loc2_ * 100 - _loc3_ * 10;
         var _loc5_:MovieClip = getChildByName("mc_wins_l") as MovieClip;
         var _loc6_:nut_num_l = _loc5_.getChildByName("mc_num100") as nut_num_l;
         var _loc7_:nut_num_l = _loc5_.getChildByName("mc_num10") as nut_num_l;
         var _loc8_:nut_num_l = _loc5_.getChildByName("mc_num1") as nut_num_l;
         if(_loc2_ > 0)
         {
            _loc5_.gotoAndStop("num_100");
            trace("test");
            _loc6_.Set(_loc2_);
            _loc7_.Set(_loc3_);
            _loc8_.Set(_loc4_);
         }
         else if(_loc3_ > 0)
         {
            _loc5_.gotoAndStop("num_10");
            _loc7_.Set(_loc3_);
            _loc8_.Set(_loc4_);
         }
         else
         {
            _loc5_.gotoAndStop("num_1");
            _loc8_.Set(_loc4_);
         }
      }
   }
}

