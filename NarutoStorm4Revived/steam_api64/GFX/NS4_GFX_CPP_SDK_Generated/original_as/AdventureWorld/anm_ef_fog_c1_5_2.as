package gametitle_fla
{
   import flash.display.MovieClip;
   import flash.events.Event;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol23")]
   public dynamic class anm_ef_fog_c1_5 extends MovieClip
   {
      
      public var m_cntFrame:*;
      
      public function anm_ef_fog_c1_5()
      {
         super();
         addFrameScript(0,this.frame1,1,this.frame2,319,this.frame320);
      }
      
      public function OnStartWait(param1:Event) : *
      {
         if(++this.m_cntFrame > 47)
         {
            visible = true;
            play();
            removeEventListener(Event.ENTER_FRAME,this.OnStartWait);
         }
      }
      
      public function OnEndWait(param1:Event) : *
      {
         if(++this.m_cntFrame > 38)
         {
            gotoAndPlay(2);
            removeEventListener(Event.ENTER_FRAME,this.OnEndWait);
         }
      }
      
      internal function frame1() : *
      {
         visible = false;
      }
      
      internal function frame2() : *
      {
         this.m_cntFrame = 0;
         stop();
         this.m_cntFrame = 0;
         this.addEventListener(Event.ENTER_FRAME,this.OnStartWait);
      }
      
      internal function frame320() : *
      {
         stop();
         visible = false;
         this.m_cntFrame = 0;
         this.addEventListener(Event.ENTER_FRAME,this.OnEndWait);
      }
   }
}

