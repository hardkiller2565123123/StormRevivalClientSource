package script.collect_skin
{
   import flash.display.MovieClip;
   import script.net_card.nut_card;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol12")]
   public dynamic class nut_skin extends MovieClip
   {
      
      public var mc_brank:MovieClip;
      
      public var mc_card:nut_card;
      
      public var mc_win:MovieClip;
      
      public function nut_skin()
      {
         super();
         addFrameScript(6,this.frame7,12,this.frame13);
      }
      
      internal function frame7() : *
      {
         stop();
      }
      
      internal function frame13() : *
      {
         stop();
      }
   }
}

