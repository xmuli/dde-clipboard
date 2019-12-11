/*
 * Copyright (C) 2018 ~ 2025 Deepin Technology Co., Ltd.
 *
 * Author:     fanpengcheng <fanpengcheng_cm@deepin.com>
 *
 * Maintainer: fanpengcheng <fanpengcheng_cm@deepin.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef ITEMBASEWIDGET_H
#define ITEMBASEWIDGET_H
#include <DWidget>
#include <DLabel>

#include <QDateTime>
#include <QPointer>

#include "itemdata.h"
#include "iconbutton.h"

DWIDGET_USE_NAMESPACE

class QTimer;
class QVBoxLayout;
class PixmapLabel;
class ItemWidget : public DWidget
{
    Q_OBJECT
public:
    ItemWidget(QPointer<ItemData> data, QWidget *parent = nullptr);

    void setText(const QString &text, const QString &length);
    void setPixmap(const QPixmap &pixmap);              //设置图像缩略图
    void setFilePixmap(const QPixmap &pixmap);          //单个文件
    void setFilePixmaps(const QList<QPixmap> &list);    //多个文件
    void setClipType(const QString &text);              //剪贴类型
    void setCreateTime(const QDateTime &time);

    //--- set style
    void setAlpha(int alpha);

    int hoverAlpha() const;
    void setHoverAlpha(int alpha);

    int unHoverAlpha() const;
    void setUnHoverAlpha(int alpha);

    int radius() {return m_radius;}
    void setRadius(int radius);

Q_SIGNALS:
    void close();
    void hoverStateChanged(bool);
    void closeHasFocus(bool has);

public Q_SLOTS:
    void onHoverStateChanged(bool hover);

private Q_SLOTS:
    void onRefreshTime();

private:
    void initUI();
    void initData(QPointer<ItemData> data);
    void initConnect();

    QString CreateTimeString(const QDateTime &time);

private:
    QPointer<ItemData> m_data;

    // title
    DLabel *m_nameLabel = nullptr;
    DLabel *m_timeLabel = nullptr;
    IconButton *m_closeButton = nullptr;

    // content
    PixmapLabel *m_contentLabel = nullptr;
    DLabel *m_statusLabel = nullptr;

    QTimer *m_refreshTimer = nullptr;
    QVBoxLayout *m_layout = nullptr;

    //--- data
    QPixmap m_pixmap;       //原始图片
    QDateTime m_createTime;

    //--- set style
    int m_radius = 0;
    int m_hoverAlpha = 0;
    int m_unHoverAlpha = 0;
    bool m_havor = false;
    bool m_closeFocus = false;  //关闭按钮是否置于选中状态
    bool m_enabled = true;

protected:
    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void mouseDoubleClickEvent(QMouseEvent *event) override;
    virtual void enterEvent(QEvent *event) override;
    virtual void leaveEvent(QEvent *event) override;
    virtual void focusInEvent(QFocusEvent *event) override;
    virtual void focusOutEvent(QFocusEvent *event) override;
};
#endif // ITEMBASEWIDGET_H
