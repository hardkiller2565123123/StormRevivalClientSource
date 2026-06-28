package script.duel_cmn
{
   import flash.display.MovieClip;
   import flash.events.Event;
   import script.duel_cmn_lang.nut_hit;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol266")]
   public class nut_combo extends MovieClip
   {
      
      public static const COMBO_START_COUNT:* = 2;
      
      public var mc_num1:MovieClip;
      
      public var mc_num10:MovieClip;
      
      public var mc_hit:nut_hit;
      
      public var mc_num100:MovieClip;
      
      public var m_count:Number;
      
      public var m_comboLevel:int;
      
      public var m_isUp:Boolean;
      
      public var m_isEnd:Boolean;
      
      public function nut_combo()
      {
         super();
         addFrameScript(7,this.frame8,17,this.frame18,25,this.frame26,35,this.frame36,43,this.frame44,53,this.frame54,61,this.frame62,71,this.frame72,79,this.frame80,89,this.frame90);
         this.m_count = 0;
         this.m_comboLevel = 0;
         this.m_isUp = false;
         this.m_isEnd = false;
         this.stop();
      }
      
      public function Initialize() : *
      {
         this.m_count = 0;
         addEventListener(Event.ENTER_FRAME,this.Update);
      }
      
      public function Finalize() : *
      {
         removeEventListener(Event.ENTER_FRAME,this.Update);
      }
      
      public function Update(param1:Event) : *
      {
         var _loc2_:int = 0;
         var _loc3_:String = null;
         var _loc4_:int = 0;
         var _loc5_:int = 0;
         var _loc6_:int = 0;
         var _loc7_:String = null;
         if(this.m_isUp)
         {
            _loc2_ = this.m_comboLevel;
            if(this.m_count > 99)
            {
               this.m_comboLevel = 5;
            }
            else if(this.m_count > 29)
            {
               this.m_comboLevel = 4;
            }
            else if(this.m_count > 19)
            {
               this.m_comboLevel = 3;
            }
            else if(this.m_count > 9)
            {
               this.m_comboLevel = 2;
            }
            else
            {
               this.m_comboLevel = 1;
            }
            if(_loc2_ != this.m_comboLevel)
            {
               _loc3_ = "in_";
               trace(_loc3_ + this.m_comboLevel.toString());
               this.gotoAndPlay(_loc3_ + this.m_comboLevel.toString());
            }
            if(this.m_count <= 999)
            {
               _loc4_ = this.m_count / 100;
               _loc5_ = (this.m_count - _loc4_ * 100) / 10;
               _loc6_ = this.m_count % 10;
               if(this.mc_num100 != null)
               {
                  this.mc_num100.gotoAndStop(_loc4_ + 1);
               }
               if(this.mc_num10 != null)
               {
                  this.mc_num10.gotoAndStop(_loc5_ + 1);
               }
               if(this.mc_num1 != null)
               {
                  this.mc_num1.gotoAndStop(_loc6_ + 1);
               }
            }
            else
            {
               if(this.mc_num100 != null)
               {
                  this.mc_num100.gotoAndStop(10);
               }
               if(this.mc_num10 != null)
               {
                  this.mc_num10.gotoAndStop(10);
               }
               if(this.mc_num1 != null)
               {
                  this.mc_num1.gotoAndStop(10);
               }
            }
            this.m_isUp = false;
         }
         if(this.m_isEnd)
         {
            _loc7_ = "out_";
            this.gotoAndStop(_loc7_ + this.m_comboLevel.toString());
            this.gotoAndPlay(_loc7_ + this.m_comboLevel.toString());
            this.m_isEnd = false;
            this.m_count = 0;
            this.m_comboLevel = 0;
         }
      }
      
      public function SetComboCount(param1:Number) : *
      {
         if(this.m_count != param1)
         {
            if(param1 > this.m_count && param1 >= COMBO_START_COUNT)
            {
               this.m_isUp = true;
            }
            if(this.m_count > param1 && this.m_count >= COMBO_START_COUNT)
            {
               this.m_isEnd = true;
            }
         }
         this.m_count = param1;
      }
      
      internal function frame8() : *
      {
         this.stop();
      }
      
      internal function frame18() : *
      {
         this.stop();
      }
      
      internal function frame26() : *
      {
         this.stop();
      }
      
      internal function frame36() : *
      {
         this.stop();
      }
      
      internal function frame44() : *
      {
         this.stop();
      }
      
      internal function frame54() : *
      {
         this.stop();
      }
      
      internal function frame62() : *
      {
         this.stop();
      }
      
      internal function frame72() : *
      {
         this.stop();
      }
      
      internal function frame80() : *
      {
         this.stop();
      }
      
      internal function frame90() : *
      {
         this.stop();
      }
   }
}

