package script.stage_logos
{
   import flash.display.MovieClip;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol26")]
   public class storm_gen extends MovieClip
   {
      
      public var mc_storm_logo:MovieClip;
      
      public function storm_gen()
      {
         super();
         addFrameScript(6,this.frame7,11,this.frame12);
      }
      
      internal function frame7() : *
      {
         stop();
      }
      
      internal function frame12() : *
      {
         stop();
      }
   }
}

