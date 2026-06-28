package script.shop_catalog
{
   import flash.display.MovieClip;
   import script.net_card.nut_card;
   import script.shop_cmn.nut_tab;
   import script.shop_cmn.nut_total;
   import script.xcmn_unset.nut_scb_bg;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol10")]
   public class nut_catalog extends MovieClip
   {
      
      public var all_win:MovieClip;
      
      public var mc_card:nut_card;
      
      public var mc_head:MovieClip;
      
      public var mc_plate_nin_00:MovieClip;
      
      public var mc_plate_nin_01:MovieClip;
      
      public var mc_plate_nin_02:MovieClip;
      
      public var mc_plate_nin_03:MovieClip;
      
      public var mc_plate_nin_04:MovieClip;
      
      public var mc_plate_nin_05:MovieClip;
      
      public var mc_plate_nin_06:MovieClip;
      
      public var mc_plate_nin_07:MovieClip;
      
      public var mc_plate_nin_08:MovieClip;
      
      public var mc_plate_nin_09:MovieClip;
      
      public var mc_plate_nin_10:MovieClip;
      
      public var mc_plate_nin_11:MovieClip;
      
      public var mc_plate_nin_12:MovieClip;
      
      public var mc_plate_nin_13:MovieClip;
      
      public var mc_plate_nin_14:MovieClip;
      
      public var mc_plate_skin_00:MovieClip;
      
      public var mc_plate_skin_01:MovieClip;
      
      public var mc_plate_skin_02:MovieClip;
      
      public var mc_plate_skin_03:MovieClip;
      
      public var mc_plate_skin_04:MovieClip;
      
      public var mc_plate_skin_05:MovieClip;
      
      public var mc_plate_skin_06:MovieClip;
      
      public var mc_plate_skin_07:MovieClip;
      
      public var mc_plate_skin_08:MovieClip;
      
      public var mc_plate_skin_09:MovieClip;
      
      public var mc_plate_skin_10:MovieClip;
      
      public var mc_plate_skin_11:MovieClip;
      
      public var mc_plate_skin_12:MovieClip;
      
      public var mc_plate_skin_13:MovieClip;
      
      public var mc_plate_skin_14:MovieClip;
      
      public var mc_scb_nin:nut_scb_bg;
      
      public var mc_scb_skin:nut_scb_bg;
      
      public var mc_tab:nut_tab;
      
      public var mc_total:nut_total;
      
      public function nut_catalog()
      {
         super();
         addFrameScript(6,this.frame7,12,this.frame13);
         var _loc1_:MovieClip = this["mc_total"];
         _loc1_.SetArabicLayoutRight();
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

