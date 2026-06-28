package script.net_bingo_rslt
{
   import ELoader.ExtendLoader;
   import flash.display.MovieClip;
   import flash.external.ExternalInterface;
   import flash.net.URLRequest;
   import script.icon_item.nut_icon_item;
   import script.xcmn_font.smb_font;
   import script.xcmn_tex00.nut_tex00;
   import script.xct_base1.nut_base1;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol19")]
   public class anm_book_data extends MovieClip
   {
      
      public var all_icon_item:nut_icon_item;
      
      public var txt_num:smb_font;
      
      public var dmy_charicon_l:nut_tex00;
      
      public var txt_title:smb_font;
      
      public var dmy_name_m:nut_tex00;
      
      public var txt_reward:smb_font;
      
      public var txt_item:smb_font;
      
      public var mc_clear:anm_clear;
      
      public var all_base1:nut_base1;
      
      private var m_iconLoader:ExtendLoader = new ExtendLoader();
      
      private var m_nameLoader:ExtendLoader = new ExtendLoader();
      
      private var m_dmyIcon:MovieClip = null;
      
      private var m_dmyName:MovieClip = null;
      
      private var m_iconPath:String = "";
      
      private var m_namePath:String = "";
      
      private var m_isDowned:Boolean = false;
      
      private var m_itemMsgId:String = "";
      
      private var m_itemNum:int = 0;
      
      private var m_categoryNo:int = 0;
      
      private var m_xfbinname:String = "";
      
      private var m_title:smb_font = null;
      
      public function anm_book_data()
      {
         super();
         addFrameScript(0,this.frame1);
         this.m_dmyIcon = this["dmy_charicon_l"];
         this.m_dmyName = this["dmy_name_m"];
         this.m_title = this["txt_title"];
         this.m_title.SetText(String(ExternalInterface.call("MessageConvert","network_sys_202")));
         this.txt_reward.SetText(String(ExternalInterface.call("MessageConvert","network_sys_204")));
         gotoAndStop("off");
      }
      
      public function SetIconCode(param1:String) : *
      {
         this.m_iconPath = "../charicon_l/l_" + param1 + ".xfbin";
         trace(this.m_iconPath);
         var _loc2_:URLRequest = new URLRequest(this.m_iconPath);
         this.m_iconLoader.load(_loc2_);
         this.m_dmyIcon.addChild(this.m_iconLoader);
         this.m_iconLoader.SetPivot(ExtendLoader.CCD_PIVOT_CENTER_CENTER);
      }
      
      public function SetNameCode(param1:String) : *
      {
         this.m_namePath = "../name_m/LANG/nm_" + param1 + ".xfbin";
         trace(this.m_namePath);
         var _loc2_:URLRequest = new URLRequest(this.m_namePath);
         this.m_nameLoader.load(_loc2_);
         this.m_dmyName.addChild(this.m_nameLoader);
         this.m_nameLoader.SetPivot(ExtendLoader.CCD_PIVOT_CENTER_CENTER);
      }
      
      public function SetDowned() : *
      {
         this.m_isDowned = true;
         gotoAndPlay("comp_loop");
      }
      
      public function SetItemInfo(param1:String, param2:int, param3:int, param4:String) : *
      {
         this.m_itemMsgId = param1;
         this.m_itemNum = param2;
         this.m_categoryNo = param3;
         this.m_xfbinname = param4;
      }
      
      public function IsLoaded() : Boolean
      {
         return this.m_iconLoader.IsLoadedXfbin() && this.m_nameLoader.IsLoadedXfbin();
      }
      
      public function IsDowned() : Boolean
      {
         return currentLabel == "comp_loop" ? true : false;
      }
      
      public function GetIconDataPath() : String
      {
         return this.m_iconPath;
      }
      
      public function GetNameDataPath() : String
      {
         return this.m_namePath;
      }
      
      public function GetItemName() : String
      {
         return this.m_itemMsgId;
      }
      
      public function GetItemNum() : uint
      {
         return this.m_itemNum;
      }
      
      public function GetItemCategoryNo() : uint
      {
         return this.m_categoryNo;
      }
      
      public function GetItemXfbin() : String
      {
         return this.m_xfbinname;
      }
      
      internal function frame1() : *
      {
         this.txt_title.SetTextColor(9718306);
         this.txt_title.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_title.SetTextFieldWidth(335);
         this.txt_title.SetTextFit(true);
         this.txt_reward.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_reward.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_item.SetTextColor(8585987);
         this.txt_item.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_num.SetTextColor(8585987);
         this.txt_num.SetTextPivot(smb_font.CCD_PIVOT_RC);
      }
   }
}

