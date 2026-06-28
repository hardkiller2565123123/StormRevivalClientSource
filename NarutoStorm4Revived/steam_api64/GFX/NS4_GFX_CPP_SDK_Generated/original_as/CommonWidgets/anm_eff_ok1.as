package script.duel_boss
{
   import flash.display.MovieClip;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol3")]
   public dynamic class anm_eff_ok1 extends MovieClip
   {
      
      public function anm_eff_ok1()
      {
         super();
         addFrameScript(12,this.frame13);
      }
      
      internal function frame13() : *
      {
         this.stop();
      }
   }
}

