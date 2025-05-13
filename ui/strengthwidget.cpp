#include "strengthwidget.h"
#include "passwordutils.h"
#include <QVBoxLayout>
#include <QFile>
#include <QTextStream>

static QStringList builtInCommon = {
    "123456","password","123456789","12345678","qwerty",
    "111111","abc123","1234567","password1","12345"
};

StrengthWidget::StrengthWidget(QWidget *parent) : ToolBase(parent)
{
    // larger font
    QFont f = font(); f.setPointSize(f.pointSize()+2); setFont(f);

    auto lay = new QVBoxLayout(this);

    inp = new QLineEdit;  inp->setEchoMode(QLineEdit::Password);
    eyeBtn = new QPushButton("👁"); eyeBtn->setFixedWidth(30);

    auto h1 = new QHBoxLayout; h1->addWidget(inp); h1->addWidget(eyeBtn);

    sensBox = new QComboBox;
    sensBox->addItems({"High","Medium","Low"});

    res = new QLabel;

    lay->addWidget(new QLabel("Password:"));
    lay->addLayout(h1);
    lay->addWidget(new QLabel("Strength sensitivity:"));
    lay->addWidget(sensBox);
    lay->addWidget(res);
    lay->addStretch();

    connect(inp,&QLineEdit::textChanged,this,&StrengthWidget::check);
    connect(sensBox,&QComboBox::currentTextChanged,this,&StrengthWidget::check);
    connect(eyeBtn,&QPushButton::clicked,this,&StrengthWidget::toggleEcho);
}

void StrengthWidget::toggleEcho()
{
    bool hide = inp->echoMode()==QLineEdit::Password;
    inp->setEchoMode(hide? QLineEdit::Normal : QLineEdit::Password);
    eyeBtn->setText(hide? "🙈" : "👁");
}

bool StrengthWidget::isCommon(const QString& pwd) const
{
    if (builtInCommon.contains(pwd, Qt::CaseInsensitive)) return true;
    QFile f("common_pw.txt");
    if (f.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QTextStream ts(&f); QString line;
        while (ts.readLineInto(&line))
            if (line.trimmed().compare(pwd,Qt::CaseInsensitive)==0)
                return true;
    }
    return false;
}

bool StrengthWidget::hasSequential(const QString& s, int run) const
{
    for (int i=0;i+run<=s.size();++i)
    {
        bool asc=true;
        for (int j=1;j<run;++j)
            if (s[i+j].unicode()!=s[i].unicode()+j){ asc=false; break; }
        if (asc) return true;
    }
    return false;
}

void StrengthWidget::check()
{
    QString p = inp->text();
    if (p.isEmpty()){ res->clear(); return; }

    const QString mode = sensBox->currentText();   // High / Medium / Low

    // 1) dictionary / sequential penalties
    if (mode=="High")
    {
        if (isCommon(p) || hasSequential(p,3))
        { res->setText("<font color='red'>Weak – common / sequential</font>"); return; }
    }
    else if (mode=="Medium")
    {
        // keep dictionary check but be lenient on sequential (<4 ignored)
        if (isCommon(p) || hasSequential(p,4))
        { res->setText("<font color='red'>Weak – common / sequential</font>"); return; }
    }
    // Low sensitivity: skip those checks entirely

    // 2) baseline strength from util
    QString base = QString::fromStdString(PasswordUtils::evaluate(p.toStdString()));

    // 3) sensitivity adjustment
    QString final = base;
    if (mode=="Medium" && base=="Moderate") final = "Strong";
    if (mode=="Low")
    {
        if (base=="Moderate") final = "Strong";
        else if (base=="Weak") final = "Moderate";
    }

    QColor color = (final=="Strong") ? Qt::green :
                       (final=="Moderate") ? QColor("#ffa726") :
                       Qt::red;
    res->setText(QString("<font color='%1'>%2</font>").arg(color.name(), final));
}
