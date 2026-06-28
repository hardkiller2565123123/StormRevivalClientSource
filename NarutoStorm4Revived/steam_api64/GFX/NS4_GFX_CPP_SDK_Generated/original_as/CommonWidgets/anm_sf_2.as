package script.duel_boss_sf
{
   import flash.display.MovieClip;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol18")]
   public dynamic class anm_sf extends MovieClip
   {
      
      public var mc_mark:MovieClip;
      
      public function anm_sf()
      {
         super();
         addFrameScript(0,this.frame1,19,this.frame20,26,this.frame27);
      }
      
      internal function frame1() : *
      {
         this.stop();
      }
      
      internal function frame20() : *
      {
         this.stop();
      }
      
      internal function frame27() : *
      {
         this.stop();
      }
   }
}

