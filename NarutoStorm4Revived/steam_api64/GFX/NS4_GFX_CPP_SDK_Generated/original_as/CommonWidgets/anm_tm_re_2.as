package script.duel_boss
{
   import flash.display.MovieClip;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol54")]
   public class anm_tm_re extends MovieClip
   {
      
      public var mc_dot1:MovieClip;
      
      public var mc_dot2:MovieClip;
      
      public var mc_dot3:MovieClip;
      
      public var mc_dot4:MovieClip;
      
      public var mc_dot5:MovieClip;
      
      public var mc_dot6:MovieClip;
      
      public var mc_dot7:MovieClip;
      
      public var mc_dot8:MovieClip;
      
      private var m_gaugeIcon:Array = new Array();
      
      private var m_maxTime:uint = 0;
      
      private var m_isTimeUp:Boolean = false;
      
      public function anm_tm_re()
      {
         super();
         addFrameScript(10,this.frame11,15,this.frame16,20,this.frame21,23,this.frame24,34,this.frame35,41,this.frame42);
         this.m_gaugeIcon.push(MovieClip(getChildByName("mc_dot1")));
         this.m_gaugeIcon.push(MovieClip(getChildByName("mc_dot2")));
         this.m_gaugeIcon.push(MovieClip(getChildByName("mc_dot3")));
         this.m_gaugeIcon.push(MovieClip(getChildByName("mc_dot4")));
         this.m_gaugeIcon.push(MovieClip(getChildByName("mc_dot5")));
         this.m_gaugeIcon.push(MovieClip(getChildByName("mc_dot6")));
         this.m_gaugeIcon.push(MovieClip(getChildByName("mc_dot7")));
         this.m_gaugeIcon.push(MovieClip(getChildByName("mc_dot8")));
         var _loc1_:int = 0;
         while(_loc1_ < this.m_gaugeIcon.length)
         {
            this.m_gaugeIcon[_loc1_].gotoAndStop("on");
            _loc1_++;
         }
      }
      
      public function SetTimeMax(param1:uint) : *
      {
         this.m_maxTime = param1;
         this.m_isTimeUp = false;
      }
      
      public function Update(param1:uint) : *
      {
         var _loc2_:int = 0;
         var _loc3_:int = 0;
         if(param1 <= this.m_maxTime - 1)
         {
            _loc2_ = int(this.m_gaugeIcon.length);
            _loc3_ = int(param1 / this.m_maxTime * _loc2_ + 0.5);
            if(_loc3_ < 0)
            {
               _loc3_ = 0;
            }
            if(_loc3_ > _loc2_ - 1)
            {
               _loc3_ = _loc2_ - 1;
            }
            if(this.m_gaugeIcon[_loc3_])
            {
               if(this.m_gaugeIcon[_loc3_].currentLabel == "on")
               {
                  this.m_gaugeIcon[_loc3_].gotoAndPlay("off");
               }
            }
            this.m_isTimeUp = false;
         }
         else
         {
            this.m_isTimeUp = true;
         }
      }
      
      public function IsTimeUp() : Boolean
      {
         return this.m_isTimeUp;
      }
      
      internal function frame11() : *
      {
         this.stop();
      }
      
      internal function frame16() : *
      {
         gotoAndPlay("lv1");
      }
      
      internal function frame21() : *
      {
         gotoAndPlay("lv2");
      }
      
      internal function frame24() : *
      {
         gotoAndPlay("lv3");
      }
      
      internal function frame35() : *
      {
         this.stop();
      }
      
      internal function frame42() : *
      {
         this.stop();
      }
   }
}

