package script.duel_cmn
{
   import flash.display.MovieClip;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol292")]
   public class nut_jutu extends MovieClip
   {
      
      public var mc_credit:MovieClip;
      
      public var m_step:Number = 0;
      
      public var m_use:Boolean = false;
      
      public var m_life:Number = 75;
      
      public var m_Recycle:Boolean = false;
      
      public var m_outflame_max:Number = 0;
      
      public var m_outflame_now:Number = 0;
      
      public var m_outflame_add:Number = 0;
      
      public function nut_jutu()
      {
         super();
         addFrameScript(0,this.frame1,3,this.frame4,6,this.frame7,9,this.frame10);
         this.visible = false;
         this.stop();
      }
      
      public function Update() : *
      {
         if(this.m_use == true)
         {
            if(this.m_step > 3)
            {
               this.SetDead();
               return;
            }
            if(this.m_life >= 0)
            {
               --this.m_life;
               if(this.m_life < 0)
               {
                  this.SetDead();
               }
            }
            else if(this.mc_credit.currentFrame == this.mc_credit.totalFrames)
            {
               this.SetDead();
            }
         }
         else
         {
            this.m_step = 0;
            this.visible = false;
         }
      }
      
      public function SetSkillName(param1:String, param2:Number, param3:Boolean) : *
      {
         if(this.m_use == true)
         {
            return;
         }
         this.visible = param3;
         this.m_use = true;
         this.m_step = 0;
         this.m_life = 75;
      }
      
      public function SetStepUp() : *
      {
         if(this.m_use == false)
         {
            return;
         }
         ++this.m_step;
         if(this.m_step == 1)
         {
            this.gotoAndPlay("jutu1");
         }
         else if(this.m_step == 2)
         {
            this.gotoAndPlay("jutu2");
         }
         else if(this.m_step == 3)
         {
            this.gotoAndPlay("jutu3");
         }
         else if(this.m_step > 3)
         {
            this.SetDead();
         }
      }
      
      public function SetDead() : void
      {
         this.gotoAndStop("jutu1");
         this.m_life = -1;
         this.m_step = 0;
         this.m_use = false;
         this.m_Recycle = true;
         this.visible = false;
      }
      
      internal function frame1() : *
      {
         this.stop();
      }
      
      internal function frame4() : *
      {
         this.stop();
      }
      
      internal function frame7() : *
      {
         this.stop();
      }
      
      internal function frame10() : *
      {
         this.stop();
      }
   }
}

