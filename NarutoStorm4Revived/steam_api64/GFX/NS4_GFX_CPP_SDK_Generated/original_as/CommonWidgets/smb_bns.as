package script.net_bonus
{
   import ELoader.ExtendLoader;
   import SeIdList.SeId;
   import flash.display.MovieClip;
   import flash.external.ExternalInterface;
   import flash.net.URLRequest;
   import script.xcmn_tex00.nut_tex00;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol12")]
   public class smb_bns extends MovieClip
   {
      
      public static const CCD_ITEM_RANK_BRONZE:int = 1;
      
      public static const CCD_ITEM_RANK_SILVER:int = 2;
      
      public static const CCD_ITEM_RANK_GOLD:int = 3;
      
      public static const CCD_ITEM_RANK_PLATINUM:int = 4;
      
      public static const CCD_ITEM_RANK_PACK:int = 5;
      
      public static const CCD_ITEM_TYPE_KUNAI:int = 1;
      
      public static const CCD_ITEM_TYPE_KAMEN:int = 2;
      
      public static const CCD_ITEM_TYPE_MAKIMONO:int = 3;
      
      public static const CCD_ITEM_TYPE_KATANA:int = 4;
      
      public static const CCD_ITEM_TYPE_SYURIKEN:int = 5;
      
      public var all_icon_check:MovieClip;
      
      public var item_dmy:nut_tex00;
      
      public var mc_cursor_i:MovieClip;
      
      public var mc_item_bg:MovieClip;
      
      private var m_iconLoader:ExtendLoader = null;
      
      private var m_dmy:MovieClip = null;
      
      private var m_isGetItem:Boolean = false;
      
      public function smb_bns()
      {
         super();
         addFrameScript(0,this.frame1,1,this.frame2,33,this.frame34,56,this.frame57,57,this.frame58);
         this.m_dmy = this["item_dmy"];
      }
      
      public function SetItemIcon(param1:int, param2:int) : *
      {
         var _loc3_:URLRequest = null;
         if(param1 < CCD_ITEM_RANK_BRONZE || param1 > CCD_ITEM_RANK_PACK)
         {
            return;
         }
         if(param2 < CCD_ITEM_TYPE_KUNAI || param2 > CCD_ITEM_TYPE_SYURIKEN)
         {
            return;
         }
         if(this.m_iconLoader == null && this.m_dmy != null)
         {
            this.m_iconLoader = new ExtendLoader();
            _loc3_ = new URLRequest("../icon_item2/mtr_" + param1 + "_" + param2 + ".xfbin");
            if(param1 == CCD_ITEM_RANK_PACK)
            {
               _loc3_ = new URLRequest("../icon_item/itemicon_pack.xfbin");
            }
            this.m_iconLoader.load(_loc3_);
            this.m_dmy.addChild(this.m_iconLoader);
            this.m_iconLoader.SetPivot(ExtendLoader.CCD_PIVOT_CENTER_CENTER);
         }
      }
      
      public function RequestGetItemAnm() : *
      {
         this.m_isGetItem = true;
         gotoAndPlay("check_in");
      }
      
      public function SetIsGetItem(param1:Boolean) : *
      {
         this.m_isGetItem = param1;
         this.UnsetCursor();
      }
      
      public function SetCursor() : *
      {
         var _loc1_:String = "on";
         if(this.m_isGetItem == true)
         {
            _loc1_ = "on_check";
         }
         gotoAndStop(_loc1_);
      }
      
      public function UnsetCursor() : *
      {
         var _loc1_:String = "off";
         if(this.m_isGetItem == true)
         {
            _loc1_ = "off_check";
         }
         gotoAndStop(_loc1_);
      }
      
      internal function frame1() : *
      {
         stop();
      }
      
      internal function frame2() : *
      {
         stop();
      }
      
      internal function frame34() : *
      {
         ExternalInterface.call("RequestPlaySE",SeId.CCD_SE_ID_LOGIN_CHECK);
      }
      
      internal function frame57() : *
      {
         stop();
      }
      
      internal function frame58() : *
      {
         stop();
      }
   }
}

