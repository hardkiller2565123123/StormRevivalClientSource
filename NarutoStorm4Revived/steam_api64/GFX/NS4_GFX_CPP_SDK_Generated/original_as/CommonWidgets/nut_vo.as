package script.collect_vo
{
   import flash.display.MovieClip;
   import script.net_card.nut_card;
   import script.xcmn_unset.nut_scb_bg;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol5")]
   public dynamic class nut_vo extends MovieClip
   {
      
      public var mc_card:nut_card;
      
      public var mc_plate_00:anm_mc_plate;
      
      public var mc_scb:nut_scb_bg;
      
      public var mc_set:anm_set;
      
      public var mc_win:MovieClip;
      
      public function nut_vo()
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

