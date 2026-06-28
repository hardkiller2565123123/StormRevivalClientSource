package duel_cutin2_lang_fla
{
   import flash.display.MovieClip;
   import script.duel_cutin2_lang.nut_duel_link1;
   
   public dynamic class MainTimeline extends MovieClip
   {
      
      public var all_duel_link1:nut_duel_link1;
      
      public function MainTimeline()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         stop();
      }
   }
}

