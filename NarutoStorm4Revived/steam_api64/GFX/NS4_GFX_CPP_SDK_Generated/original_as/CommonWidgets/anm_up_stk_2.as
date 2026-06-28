package script.duel_boss
{
   import flash.display.MovieClip;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol77")]
   public class anm_up_stk extends MovieClip
   {
      
      public var mc_dot1:MovieClip;
      
      public var mc_dot10:MovieClip;
      
      public var mc_dot2:MovieClip;
      
      public var mc_dot3:MovieClip;
      
      public var mc_dot4:MovieClip;
      
      public var mc_dot5:MovieClip;
      
      public var mc_dot6:MovieClip;
      
      public var mc_dot7:MovieClip;
      
      public var mc_dot8:MovieClip;
      
      public var mc_dot9:MovieClip;
      
      private var m_gaugeIcon:Array;
      
      private var m_okEffect:Array;
      
      private var m_maxGauge:uint = 0;
      
      private var m_successVal:uint = 0;
      
      private var m_preIcon:int = 0;
      
      private var m_tensionLevel:int = 0;
      
      private var m_isSuccess:Boolean = false;
      
      public function anm_up_stk()
      {
         var _loc2_:anm_up_ok = null;
         this.m_gaugeIcon = new Array();
         this.m_okEffect = new Array();
         super();
         addFrameScript(10,this.frame11,22,this.frame23,36,this.frame37,46,this.frame47,56,this.frame57,63,this.frame64);
         this.m_gaugeIcon.push(MovieClip(getChildByName("mc_dot1")));
         this.m_gaugeIcon.push(MovieClip(getChildByName("mc_dot2")));
         this.m_gaugeIcon.push(MovieClip(getChildByName("mc_dot3")));
         this.m_gaugeIcon.push(MovieClip(getChildByName("mc_dot4")));
         this.m_gaugeIcon.push(MovieClip(getChildByName("mc_dot5")));
         this.m_gaugeIcon.push(MovieClip(getChildByName("mc_dot6")));
         this.m_gaugeIcon.push(MovieClip(getChildByName("mc_dot7")));
         this.m_gaugeIcon.push(MovieClip(getChildByName("mc_dot8")));
         this.m_gaugeIcon.push(MovieClip(getChildByName("mc_dot9")));
         this.m_gaugeIcon.push(MovieClip(getChildByName("mc_dot10")));
         var _loc1_:int = 0;
         while(_loc1_ < this.m_gaugeIcon.length)
         {
            this.m_gaugeIcon[_loc1_].gotoAndStop("off");
            _loc2_ = new anm_up_ok();
            _loc2_.visible = false;
            this.m_okEffect[_loc1_] = _loc2_;
            this.m_gaugeIcon[_loc1_].addChild(this.m_okEffect[_loc1_]);
            _loc1_++;
         }
      }
      
      public function SetGaugeMax(param1:uint) : *
      {
         this.m_maxGauge = param1;
         this.m_isSuccess = false;
      }
      
      public function SetSuccessVal(param1:uint) : *
      {
         this.m_successVal = param1;
      }
      
      public function Update(param1:uint) : *
      {
         var _loc5_:int = 0;
         var _loc2_:int = int(this.m_gaugeIcon.length);
         var _loc3_:int = int(param1 / this.m_maxGauge * _loc2_ + 0.5);
         if(_loc3_ < 0)
         {
            _loc3_ = 0;
         }
         if(_loc3_ > _loc2_)
         {
            _loc3_ = _loc2_;
         }
         if(this.m_preIcon != _loc3_)
         {
            _loc5_ = 0;
            while(_loc5_ < _loc2_)
            {
               if(_loc5_ < _loc3_)
               {
                  if(this.m_gaugeIcon[_loc5_].currentLabel == "off")
                  {
                     this.m_gaugeIcon[_loc5_].gotoAndStop("on");
                     if(Boolean(this.m_okEffect[_loc5_]) && this.m_okEffect[_loc5_].visible == false)
                     {
                        this.m_okEffect[_loc5_].visible = true;
                        this.m_okEffect[_loc5_].gotoAndPlay(1);
                     }
                  }
               }
               else if(this.m_gaugeIcon[_loc5_].currentLabel == "on")
               {
                  this.m_gaugeIcon[_loc5_].gotoAndStop("off");
                  if(this.m_okEffect[_loc5_])
                  {
                     this.m_okEffect[_loc5_].visible = false;
                  }
               }
               _loc5_++;
            }
            this.m_preIcon = _loc3_;
         }
         var _loc4_:uint = uint(param1 / this.m_maxGauge * 100);
         if(_loc4_ > 80)
         {
            this.m_tensionLevel = 3;
         }
         else if(_loc4_ > 50)
         {
            this.m_tensionLevel = 2;
         }
         else if(_loc4_ > 20)
         {
            this.m_tensionLevel = 1;
         }
         else
         {
            this.m_tensionLevel = 0;
         }
         if(_loc4_ >= this.m_successVal)
         {
            this.m_isSuccess = true;
         }
         else
         {
            this.m_isSuccess = false;
         }
      }
      
      public function IsSuccess() : Boolean
      {
         return this.m_isSuccess;
      }
      
      public function GetTensionLevel() : int
      {
         return this.m_tensionLevel;
      }
      
      internal function frame11() : *
      {
         this.stop();
      }
      
      internal function frame23() : *
      {
         gotoAndPlay("lv1_loop");
      }
      
      internal function frame37() : *
      {
         gotoAndPlay("lv2_loop");
      }
      
      internal function frame47() : *
      {
         gotoAndPlay("lv3_loop");
      }
      
      internal function frame57() : *
      {
         this.stop();
      }
      
      internal function frame64() : *
      {
         this.stop();
      }
   }
}

