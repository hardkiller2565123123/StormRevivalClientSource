package script.stage_logos
{
   import flash.display.MovieClip;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol50")]
   public class storm_four_evo extends MovieClip
   {
      
      public var mc_storm_logo:MovieClip;
      
      public function storm_four_evo()
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

